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

static void print_search_vector(const sorted_vector<int>& vec, vector<int>::iterator where)
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

static void insert_vector(sorted_vector<int>& vec, int value)
{
  cout << "insert " << value << "\t-> ";
  vec.insert(value);
  print_vector(vec);
}

static void search_vector(sorted_vector<int>& vec, int value)
{
  cout << "search " << value << "\t-> ";
  vector<int>::iterator it = vec.find(value);
  print_search_vector(vec, it);
}

void Test1()
{
  cout << "*** INSERT TEST #1 ***" << endl;
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

  cout << endl << "*** INSERT TEST #2 ***" << endl;
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

  cout << endl << "*** INSERT TEST #3 ***" << endl;
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
    insert_vector(vec,10);
    insert_vector(vec,1);
    insert_vector(vec,2);
    insert_vector(vec,11);
    insert_vector(vec,6);
    insert_vector(vec,5);
    insert_vector(vec,5);
    insert_vector(vec,12);
    insert_vector(vec,-10);

    cout << "searching existed values" << endl;

    search_vector(vec,-10);
    search_vector(vec,1);
    search_vector(vec,2);
    search_vector(vec,5);
    search_vector(vec,6);
    search_vector(vec,10);
    search_vector(vec,11);
    search_vector(vec,12);

    cout << "searching misses" << endl;

    search_vector(vec,-20);
    search_vector(vec,3);
    search_vector(vec,4);
    search_vector(vec,7);
    search_vector(vec,8);
    search_vector(vec,9);
    search_vector(vec,20);
  }
}