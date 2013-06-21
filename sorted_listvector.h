#pragma once

#include <vector>
#include <list>
#include <assert.h>

template<class T, class A = std::allocator<T>>
class sorted_vector: public std::vector<T,A>
{
public:
  void insert(const T& value)
  {
    size_t n = size();

    if(n == 0)
    {
      vector::push_back(value);
    }
    else if(n == 1)
    {
      if(at(0) < value)
      {
        vector::insert(end(),value);
      }
      else
      {
        vector::insert(begin(),value);
      }
    }
    else
    {
      // binary search
      size_t left = 0;
      size_t right = n - 1;

      while(right - left >= 1)
      {
        if(at(left) >= value)
        {
          vector::insert(begin() + left, value);
          return;
        }

        if(at(right) <= value)
        {
          vector::insert(begin() + right + 1, value);
          return;
        }

        if(right - left == 1)
        {
          vector::insert(begin() + right, value);
          return;
        }

        size_t mid = left + ((right - left) >> 1);
        if(mid == left)
        {
          vector::insert(begin() + left, value);
          return;
        }

        const T& midVal = at(mid);
        if(midVal == value)
        {
          vector::insert(begin() + mid, value);
          return;
        }
        else if(value < midVal)
        {
          right = mid;
        }
        else // value > midVal
        {
          left = mid;
        }
      }

      assert(0);
    }
  }

  iterator find(const T& value)
  {
    // TODO:
  }

  bool has(const T& value)
  {
    return find(value) != end();
  }

  const T& left()
  {
    assert(size() != 0);
    return *begin();
  }

  const T& right()
  {
    assert(size() != 0);
    return *rend();
  }
};

template<class T>
class sorted_listvector
{
public:
  void insert(T value)
  {
    std::list< sorted_vector<T> >::iterator it = mList.begin();

    if(it == mList.end()) // insert first value
    {
      sorted_vector<T> vec;
      vec.insert(value);
      mList.push_back(vec);
    }

    // TODO:
  }

  bool has(const T& value)
  {
    // TODO:
  }

private:
  std::list< sorted_vector<T> > mList;
};