#include "stdafx.h"
#include "sorted_listvector.h"
#include <iostream>

using namespace std;

static bool is_vector_sorted(const sorted_vector<int>& vec)
{
  bool sorted = true;
  int prev = INT_MIN;
  for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
  {
    int cur = *it;
    if(prev > cur)
    {
      sorted = false;
    }
    prev = cur;
  }
  return sorted;
}

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

static void print_search_vector(const sorted_vector<int>& vec, vector<int>::const_iterator where)
{
  cout << "[" << vec.size() << "]={";
  int prev = INT_MIN;
  for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
  {
    cout << " ";

    if(where == it)
    {
      cout << ">";
    }

    int cur = *it;
    if(prev > cur)
    {
      cout << "ERROR->";
    }
    prev = cur;

    cout << cur;

    if(where == it)
    {
      cout << "<";
    }
  }
  cout << " }";
  if(where == vec.end())
  {
    cout << " not found";
  }
  cout << endl;
}

static void insert_vector(sorted_vector<int>& vec, int val)
{
  cout << "insert " << val << "\t-> ";
  vec.insert(val);
  print_vector(vec);
}

static bool search_vector(sorted_vector<int>& vec, int val)
{
  cout << "search " << val << "\t-> ";
  vector<int>::const_iterator it = vec.find(val);
  print_search_vector(vec, it);
  return it != vec.end();
}

void Test1()
{
  cout << "*** INSERT TEST #1 ***" << endl;
  {
    sorted_vector<int> vec;
    int input[] = {10, 1, 2, 11, 6, 5, 5, 12, -10, 5};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_vector(vec,input[i]);
      if(!is_vector_sorted(vec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << endl << "*** INSERT TEST #2 ***" << endl;
  {
    sorted_vector<int> vec;
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_vector(vec,input[i]);
      if(!is_vector_sorted(vec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << endl << "*** INSERT TEST #3 ***" << endl;
  {
    sorted_vector<int> vec;
    int input[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_vector(vec,input[i]);
      if(!is_vector_sorted(vec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }

  cout << "TEST PASSED" << endl;
}

void Test2()
{
  for(int i = 0; i<10; ++i)
  {
    cout << "*** SORT TEST #" << i << " ***" << endl;
    sorted_vector<int> vec;
    for(int j = 0; j<24; ++j)
    {
      insert_vector(vec,rand()%10);
      if(!is_vector_sorted(vec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
  }
  cout << "TEST PASSED" << endl;
}

void Test3()
{
  cout << "*** SEARCH TEST ***" << endl;
  {
    sorted_vector<int> vec;
    int input[] = {10, 1, 2, 11, 6, 5, 5, 12, -10, 5};
    for(int i = 0; i < sizeof(input)/sizeof(int); ++i)
    {
      insert_vector(vec,input[i]);
      if(!is_vector_sorted(vec))
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }

    cout << "\tSearching existed values:" << endl;
    int search[] = {-10, 1, 2, 5, 6, 10, 11, 12};
    for(int i = 0; i < sizeof(search)/sizeof(int); ++i)
    {
      bool found = search_vector(vec, search[i]);
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
      bool found = search_vector(vec, missed[i]);
      if(found)
      {
        cout << "*** ERROR *** TEST FAILED ***" << endl;
        return;
      }
    }
    cout << "TEST PASSED" << endl;
  }
}