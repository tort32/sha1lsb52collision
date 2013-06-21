#include "stdafx.h"
#include "sorted_listvector.h"
#include <iostream>

using namespace std;


static void print_vector(const sorted_vector<int>& vec)
{
  cout << "[" << vec.size() << "]={";
  int prev = INT_MIN;
  for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
  {
    cout << " ";

    int cur = *it;
    if(prev > cur)
    {
      cout << "ERROR->";
    }
    prev = cur;

    cout << cur;
  }
  cout << " }" << endl;
}

static void insert_vector(sorted_vector<int>& vec, int value)
{
  cout << "insert " << value << "\t-> ";
  vec.insert(value);
  print_vector(vec);
}

void Test1()
{
  cout << "*** TEST #1 ***" << endl;
  {
    sorted_vector<int> vec;
    insert_vector(vec,10);
    insert_vector(vec,1);
    insert_vector(vec,2);
    insert_vector(vec,11);
    insert_vector(vec,6);
    insert_vector(vec,5);
    insert_vector(vec,5);
    insert_vector(vec,12);
    insert_vector(vec,-10);
  }

  cout << endl << "*** TEST #2 ***" << endl;
  {
    sorted_vector<int> vec;
    insert_vector(vec,1);
    insert_vector(vec,2);
    insert_vector(vec,3);
    insert_vector(vec,4);
    insert_vector(vec,5);
    insert_vector(vec,6);
    insert_vector(vec,7);
    insert_vector(vec,8);
    insert_vector(vec,9);
  }

  cout << endl << "*** TEST #3 ***" << endl;
  {
    sorted_vector<int> vec;
    insert_vector(vec,9);
    insert_vector(vec,8);
    insert_vector(vec,7);
    insert_vector(vec,6);
    insert_vector(vec,5);
    insert_vector(vec,4);
    insert_vector(vec,3);
    insert_vector(vec,2);
    insert_vector(vec,1);
  }
}