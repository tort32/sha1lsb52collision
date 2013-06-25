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
    // binary search
    size_t left = 0; // inclusive index
    size_t right = size(); // exclusive index

    while(right > left)
    {
      if(at(left) >= value)
      {
        vector::insert(begin() + left, value);
        return;
      }

      if(value >= at(right - 1))
      {
        vector::insert(begin() + right, value);
        return;
      }

      // found two nearest elements and the value between them
      // at(left) < value < at(right - 1)
      if( left + 1 == right - 1 )
      {
        vector::insert(begin() + left + 1, value);
        return;
      }

      // split a range
      size_t mid = left + ((right - left) >> 1);

      // choose a side
      if(value < at(mid))
      {
        right = mid;
      }
      else // value >= at(mid)
      {
        left = mid;
      }
    }

    vector::push_back(value);
  }

  iterator find(const T& value)
  {
    // binary search
    size_t left = 0; // inclusive index
    size_t right = size(); // exclusive index

    while(right > left)
    {
      if(at(left) == value)
      {
        return begin() + left;
      }

      if(at(right - 1) == value)
      {
        return begin() + (right - 1);
      }

      if(at(left) > value)
      {
        return end();
      }

      if(value > at(right - 1))
      {
        return end();
      }

      // found two nearest elements and the value between them
      // at(left) < value < at(right - 1)
      if( left + 1 == right - 1 )
      {
        return end();
      }

      // split a range
      size_t mid = left + ((right - left) >> 1);

      // choose a side
      if(value < at(mid))
      {
        right = mid;
      }
      else // value >= at(mid)
      {
        left = mid;
      }
    }

    return end();
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