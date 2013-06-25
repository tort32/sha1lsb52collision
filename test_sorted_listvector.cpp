#include "stdafx.h"
#include "sorted_listvector.h"
#include <iostream>

using namespace std;

static bool is_listvector_sorted(const sorted_listvector<int>& listvec)
{
  bool sorted = true;
  int prev = INT_MIN;
  for(list<sorted_vector<int> >::const_iterator itList = listvec.begin(), itListEnd = listvec.end(); itList != itListEnd; ++itList)
  {
    for(vector<int>::const_iterator itVec = itList->begin(), itVecEnd = itList->end(); itVec != itVecEnd; ++itVec)
    {
      int cur = *itVec;
      if(prev > cur)
      {
        sorted = false;
      }
      prev = cur;
    }
  }
  return sorted;
}

static void print_listvector(const sorted_listvector<int>& listvec)
{
  cout << "[" << listvec.size() << "]=" << endl;
  int prev = INT_MIN;
  int cur = 0;
  for(list<sorted_vector<int> >::const_iterator itList = listvec.begin(), itListEnd = listvec.end(); itList != itListEnd; ++itList)
  {
    cout << "  " << cur++ << ":[" << itList->size() << "]={";
    for(vector<int>::const_iterator itVec = itList->begin(), itVecEnd = itList->end(); itVec != itVecEnd; ++itVec)
    {
      cout << " ";

      int cur = *itVec;

      if(prev > cur)
      {
        cout << "ERROR->";
      }
      prev = cur;

      cout << cur;
    }
    cout << " }" << endl;
  }
}

static void insert_listvector(sorted_listvector<int>& listvec, int val)
{
  cout << "insert " << val << "\t-> ";
  listvec.insert(val);
  print_listvector(listvec);
}

static bool search_listvector(sorted_listvector<int>& listvec, int val)
{
  cout << "search " << val << "\t-> ";
  bool found = listvec.has(val);
  cout << (found ? "found" : "not found") << endl;
  return found;
}

void Test4()
{
  cout << "*** INSERT TEST #1 ***" << endl;
  {
    sorted_listvector<int> listvec(4);
    int input[] = {10, 1, 2, 11, 6, 5, 5, 12, -10, 5};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_listvector(listvec, input[i]);
      if(!is_listvector_sorted(listvec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << endl << "*** INSERT TEST #2 ***" << endl;
  {
    sorted_listvector<int> listvec(4);
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_listvector(listvec,input[i]);
      if(!is_listvector_sorted(listvec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << endl << "*** INSERT TEST #3 ***" << endl;
  {
    sorted_listvector<int> listvec(4);
    int input[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_listvector(listvec,input[i]);
      if(!is_listvector_sorted(listvec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << "TEST PASSED" << endl;
}

void Test5()
{
  for(int i = 0; i<10; ++i)
  {
    cout << "*** SORT TEST #" << i << " ***" << endl;
    sorted_listvector<int> listvec(4);
    for(int j = 0; j<24; ++j)
    {
      insert_listvector(listvec,rand()%10);
      if(!is_listvector_sorted(listvec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }
  cout << "TEST PASSED" << endl;
}

void Test6()
{
  cout << "*** FILL TEST ***" << endl;

  const int count = 1000;
  vector<int> input;
  for(int j = 0; j<count; ++j)
  {
    size_t size = input.size();
    size_t pos = size != 0 ? rand() % (size+1) : 0;
    input.insert(input.end() - pos, j);
  }

  sorted_listvector<int> listvec(128);
  for(int j = 0; j<count; ++j)
  {
    listvec.insert(input[j]);
  }
  print_listvector(listvec);

  if(!is_listvector_sorted(listvec))
  {
    cout << "*** ERROR *** TEST FAILED ***" << endl;
    return;
  }

  size_t total = listvec.size_total();
  size_t capacity = listvec.capacity_total();
  cout << "Fill ratio: " << total << "/" << capacity << " = " << (100.f*(float)total/(float)capacity) << "%%" << endl;

  cout << "TEST PASSED" << endl;
}

void Test7()
{
  cout << "*** SEARCH TEST ***" << endl;
  {
    sorted_listvector<int> listvec(4);
    int input[] = {10, 1, 2, 11, 6, 5, 5, 12, -10, 5};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      listvec.insert(input[i]);
      if(!is_listvector_sorted(listvec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
    print_listvector(listvec);

    cout << "\tSearching existed values:" << endl;
    int search[] = {-10, 1, 2, 5, 6, 10, 11, 12};
    for(int i = 0; i < sizeof(search)/sizeof(int); ++i)
    {
      bool found = search_listvector(listvec, search[i]);
      if(!found)
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }

    cout << "\tSearching missed values" << endl;
    int missed[] = {-20, 3, 4, 7, 8, 9, 20};
    for(int i = 0; i < sizeof(missed)/sizeof(int); ++i)
    {
      bool found = search_listvector(listvec, missed[i]);
      if(found)
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
    cout << "TEST PASSED" << endl;
  }
}
