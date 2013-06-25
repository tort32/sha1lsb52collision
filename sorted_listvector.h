#pragma once

#include "stdafx.h"
#include <assert.h>

template<class T, class A = std::allocator<T>>
class sorted_vector: public std::vector<T,A>
{
public:
  sorted_vector(): vector() {}

  sorted_vector(iterator from, iterator to): vector(from, to) {} // supposed input range is sorted

  void insert(const T& val)
  {
    // binary search
    size_t left = 0; // inclusive index
    size_t right = size(); // exclusive index

    while(right > left)
    {
      if(at(left) >= val)
      {
        vector::insert(begin() + left, val);
        return;
      }

      if(val >= at(right - 1))
      {
        vector::insert(begin() + right, val);
        return;
      }

      // found two nearest elements and the value between them
      // at(left) < value < at(right - 1)
      if( left + 1 == right - 1 )
      {
        vector::insert(begin() + left + 1, val);
        return;
      }

      // split a range
      size_t mid = left + ((right - left) >> 1);

      // choose a side
      if(val < at(mid))
      {
        right = mid;
      }
      else // value >= at(mid)
      {
        left = mid;
      }
    }

    vector::push_back(val);
  }

  const_iterator find(const T& val) const
  {
    // binary search
    size_t left = 0; // inclusive index
    size_t right = size(); // exclusive index

    while(right > left)
    {
      if(at(left) == val)
      {
        return begin() + left;
      }

      if(at(right - 1) == val)
      {
        return begin() + (right - 1);
      }

      if(at(left) > val)
      {
        return end();
      }

      if(val > at(right - 1))
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
      if(val < at(mid))
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

  bool has(const T& val) const
  {
    return find(val) != end();
  }

  const T& left() const
  {
    assert(size() != 0);
    return (*this)[0];
    //return *begin();
  }

  const T& right() const
  {
    assert(size() != 0);
    //return *rend();
    return (*this)[size() - 1];
  }
};

template<class T, class A = std::allocator<T>>
class sorted_listvector: public std::list< sorted_vector<T,A> >
{
public:
  sorted_listvector(size_t batchSize = 1024) : list(), mBatchSize(batchSize) {}

  void insert(const T& val)
  {
    for(std::list< sorted_vector<T,A> >::iterator it = begin(); it != end(); ++it)
    {
      // If value is not in this range, move to the next
      std::list< sorted_vector<T,A> >::iterator itNext = it;
      if( val > it->right() && ++itNext != end())
      {
        continue;
      }

      // if the current range has place to insert
      if(it->size() < mBatchSize)
      {
        it->insert(val);
        return;
      }
      else
      {
        // split
        size_t mid = it->size() >> 1;
        sorted_vector<T,A> vecLeft(it->begin(),it->begin() + mid);
        sorted_vector<T,A> vecRight(it->begin() + mid,it->end());

        if(val < vecRight.left())
        {
          vecLeft.insert(val);
        }
        else
        {
          vecRight.insert(val);
        }

        *it = vecRight;
        list::insert(it, vecLeft);
        return;
      }
    }

    // insert first value
    {
      sorted_vector<T,A> vec;
      vec.insert(val);
      list::push_back(vec);
    }
  }

  size_t size_total() const
  {
    size_t total = 0;
    for(std::list< sorted_vector<T,A> >::const_iterator it = begin(); it != end(); ++it)
    {
      total += it->size();
    }
    return total;
  }

  size_t capacity_total() const
  {
    size_t total = 0;
    for(std::list< sorted_vector<T,A> >::const_iterator it = begin(); it != end(); ++it)
    {
      total += it->capacity();
    }
    return total;
    //return mBatchSize * size();
  }

  bool has(const T& val)
  {
    for(std::list< sorted_vector<T,A> >::iterator it = begin(); it != end(); ++it)
    {
      if( val > it->right())
      {
        continue;
      }
      else
      {
        return it->has(val);
      }
    }
    return false;
  }

private:
  size_t mBatchSize;
};

template<class T>
class listset: public std::list< std::set<T> >
{
public:
  listset(size_t batchSize = 16777216) : list(), mBatchSize(batchSize) {}

  void insert(const T& val)
  {
    for(std::list< std::set<T> >::iterator it = begin(); it != end(); ++it)
    {
      // If value is not in this range, move to the next
      std::list< std::set<T> >::iterator itNext = it;
      if( val > *(it->rbegin()) && ++itNext != end())
      {
        continue;
      }

      // if the current range has place to insert
      if(it->size() < mBatchSize)
      {
        it->insert(val);
        return;
      }
      else
      {
        // split
        size_t mid = it->size() >> 1;
        std::set<T>::iterator itMid = it->begin();
        for(size_t i = 0; i<mid; ++i) { ++itMid; }
        //std::set<T>::iterator itMid = it->begin() + mid;
        std::set<T> vecLeft(it->begin(),itMid);
        std::set<T> vecRight(itMid,it->end());

        if(val < *vecRight.begin())
        {
          vecLeft.insert(val);
        }
        else
        {
          vecRight.insert(val);
        }

        *it = vecRight;
        list::insert(it, vecLeft);
        return;
      }
    }

    // insert first value
    {
      std::set<T> vec;
      vec.insert(val);
      list::push_back(vec);
    }
  }

  uint64_t size_total() const
  {
    uint64_t total = 0;
    for(std::list< std::set<T> >::const_iterator it = begin(); it != end(); ++it)
    {
      total += it->size();
    }
    return total;
  }

  uint64_t capacity_total() const
  {
    return size() * mBatchSize;
  }

  bool has(const T& val)
  {
    for(std::list< std::set<T> >::iterator it = begin(); it != end(); ++it)
    {
      if( val > *(it->rbegin()))
      {
        continue;
      }
      else
      {
        return it->find(val) != it->end();
      }
    }
    return false;
  }

private:
  size_t mBatchSize;
};
