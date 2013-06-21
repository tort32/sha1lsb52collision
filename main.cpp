#include "stdafx.h"

#include <math.h>
#include "sha1.h"
#include <fstream>
#include <time.h>

using namespace std;

inline void generateString(uint64_t block, char str[9])
{
    // Alphabet table
    const char chars[64] =
    {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', // 26
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', // 26 + 26 = 52
        '0','1','2','3','4','5','6','7','8','9','+','-' // 52 + 12 = 64
    };

    // each 6-bit defines a char
    str[0] = chars[(block    ) & 0x3F]; //  0... 5 bit
    str[1] = chars[(block>> 6) & 0x3F]; //  6...11 bit
    str[2] = chars[(block>>12) & 0x3F]; // 12...17 bit
    str[3] = chars[(block>>18) & 0x3F]; // 18...23 bit
    str[4] = chars[(block>>24) & 0x3F]; // 24...29 bit
    str[5] = chars[(block>>30) & 0x3F]; // 30...35 bit
    str[6] = chars[(block>>36) & 0x3F]; // 36...41 bit
    str[7] = chars[(block>>42) & 0x3F]; // 42...47 bit

    str[8] = '\0';
}

// Numbers of hashes to collect to get a 50% chance of collision = 1.25 * SQRT(2^52) due to Birthday attack
// More info: http://en.wikipedia.org/wiki/Birthday_attack
const uint64_t maxBlock = 83886080LL;

// We shifting starting block to search collisions in different hash source subspaces
// This is a maximal subspace number
const uint64_t maxSubSpace = 10000000LL;

// Each 1M blocks we trace stage of processing
const uint64_t megaBlock = 1000000LL;

void method1()
{
    // This is a dumb brute force searching of a collision
    // We store hash and a string block for each step
    // Until the same hash will be found
    // Then we read the first string block given this hash

    // WARNING: storing all hashes takes a lot of memory and cause run-time error
    // It happens on 43M hashes when we need to collect 83M.
    // Not so bad. This give us 20% chance to find a collision.
    // We can search collisions with a different blocks shuffling or changing chars in the alphabet.
    // In this code starting block can be shifted to move hash source subspace.

    // Another hack is to use /LARGEADDRESSAWARE linker option to get more memory
    // This way we can collect all 83M of hash-string pairs

    ofstream fout("out.txt", ios_base::app); // file to store found collisions

    char str[9];
    memset(str, 0, 9);

    SHA1 sha;
    uint32_t sha1hash[5];

    srand(time(NULL));

    map<uint64_t, uint64_t> hashMap;

    while(1)
    {
        uint64_t subSpace = (uint64_t)((double)rand()/(double)RAND_MAX * (double)maxSubSpace);

        cout << "Computing subspace " << dec << subSpace << " (" << dec << (subSpace*maxBlock/megaBlock) << ".." << dec << ((subSpace+1)*maxBlock/megaBlock) << "M hashes)" << endl;

        for(uint64_t i = 0; i < maxBlock; ++i)
        {
            uint64_t block = i + subSpace*maxBlock;
            uint64_t hash52;
            generateString(block, str);

            sha.Reset();
            sha << str;

            if (!sha.Result(sha1hash))
            {
                cerr << "ERROR-- could not compute message digest" << endl;
                continue;
            }
            else
            {
                hash52 = LSB52(GET64(sha1hash[3],sha1hash[4]));

                map<uint64_t, uint64_t>::iterator it = hashMap.find(hash52);
                if(it == hashMap.end())
                {
                    // insert new hash-block pair
                    hashMap.insert(pair<uint64_t, uint64_t>(hash52, block));
                }
                else
                {
                    // we got a collision
                    char str2[9];
                    memset(str2, 0, 9);
                    generateString(it->second, str2);
                    cout << "Collision found on " << str << " and " << str2 << " Hash = " << hex << hash52 << endl;
                    fout << "Collision found on " << str << " and " << str2 << " Hash = " << hex << hash52 << endl;
                }
            }

            if( (i % megaBlock) == 0 )
            {
                cout << "Computed " << dec << (i/megaBlock) << "/" << dec << (maxBlock/megaBlock) << "M hashes. Last key " << str << endl;
            }
        }

        cout << "Subspace " << dec << subSpace << " is over." << endl;
        cout << "Clearing memory." << endl;

        hashMap.clear();
    }
}

void method2()
{
    // NOT YET FINISHED
    // DUE TO MEMORY ISSUES

    // Since we have no enough memory for storing all possible hashes
    // We can use smaller hash size to find a possible collision on longer hash
    // So we reject big amount of useless hashes that not colliding on smaller hash size
    set<uint32_t> hashSet24;

    char str[9];
    memset(str, 0, 9);

    SHA1 sha;
    uint32_t sha1hash[5];

    for(uint64_t block = 0; block < maxBlock; ++block)
    {
        uint32_t hash24;

        generateString(block, str);

        sha.Reset();
        sha << str;

        if (!sha.Result(sha1hash))
        {
            cerr << "ERROR-- could not compute message digest" << endl;
            continue;
        }
        else
        {
            hash24 = LSB24(GET64(sha1hash[3],sha1hash[4]));
            hashSet24.insert(hash24);
        }

        if( (block % megaBlock) == 0 )
        {
            cout << "Computed 24-bit " << dec << (block/megaBlock) << "/" << dec << (maxBlock/megaBlock) << "M hashes. Last key/hash " << str << "/" << hex << hash24 << endl;
        }
    }

    uint32_t count24 = hashSet24.size();
    float max24 = powf(2.f,24.f);
    printf("Total number of 24-bit hashes: %dM (%.2f %%)\n", count24/megaBlock, ((float)count24)/max24*100.f);

    set<uint32_t> hashSet28;
    for(uint64_t block = 0; block < maxBlock; ++block)
    {
        uint32_t hash28;

        generateString(block, str);

        sha.Reset();
        sha << str;

        if (!sha.Result(sha1hash))
        {
            cerr << "ERROR-- could not compute message digest" << endl;
            continue;
        }
        else
        {
            hash28 = LSB28(GET64(sha1hash[3],sha1hash[4]));

            // store longer hash if smaller is colliding
            uint32_t hash24 = LSB24(hash28);
            if(hashSet24.find(hash24) != hashSet24.end())
            {
                hashSet28.insert(hash28);
            }
        }

        if( (block % megaBlock) == 0 )
        {
            cout << "Computed 28-bit " << dec << (block/megaBlock) << "/" << dec << (maxBlock/megaBlock) << "M hashes. Last key/hash " << str << "/" << hex << hash28 << endl;
        }
    }

    hashSet24.clear();

    uint32_t count28 = hashSet28.size();
    float max28 = powf(2.f,28.f);
    printf("Total number of 28-bit hashes: %dM (%.2f %%)\n", count28/megaBlock, ((float)count28)/max28*100.f);

    set<uint32_t> hashSet30;
    for(uint64_t block = 0; block < maxBlock; ++block)
    {
        uint32_t hash30;

        generateString(block, str);

        sha.Reset();
        sha << str;

        if (!sha.Result(sha1hash))
        {
            cerr << "ERROR-- could not compute message digest" << endl;
            continue;
        }
        else
        {
            hash30 = LSB30(GET64(sha1hash[3],sha1hash[4]));

            // store longer hash if smaller is colliding
            uint32_t hash28 = LSB28(hash30);
            if(hashSet28.find(hash28) != hashSet28.end())
            {
                hashSet30.insert(hash30);
            }
        }

        if( (block % megaBlock) == 0 )
        {
            cout << "Computed 30-bit " << dec << (block/megaBlock) << "/" << dec << (maxBlock/megaBlock) << "M hashes. Last key/hash " << str << "/" << hex << hash30 << endl;
        }
    }

    hashSet28.clear();

    uint32_t count30 = hashSet30.size();
    float max30 = powf(2.f,30.f);
    printf("Total number of 30-bit hashes: %dM (%.2f %%)\n", count30/megaBlock, ((float)count30)/max30*100.f);
}

int main()
{
    //method1();

    Test1();

    return 0;
}
