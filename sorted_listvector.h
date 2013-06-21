#pragma once

#include <vector>
#include <list>
#include <assert.h>

template<class T>
class sorted_vector
{
public:
  void insert(const T& value)
  {
    size_t size = mVector.size();

    if(size == 0)
    {
      mVector.push_back(value);
    }
    else if(size == 1)
    {
      if(mVector[0] < value)
        mVector.push_back(value);
      else
        mVector.insert(mVector.begin(),value);
    }
    else
    {
      // binary search
      size_t left = 0;
      size_t right = size - 1;

      while(right - left <= 1)
      {
        if(mVector[left] >= value)
        {
          mVector.insert(mVector.begin() + left, value);
          return;
        }

        if(mVector[right] <= value)
        {
          mVector.insert(mVector.begin() + right + 1, value);
          return;
        }

        size_t mid = left + ((right - left) >> 1);
        if(mid == left)
        {
          mVector.insert(mVector.begin() + left, value);
          return;
        }

        const T& midVal = mVector[mid];
        if(midVal == value)
        {
          mVector.insert(mVector.begin() + mid, value);
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
    }
  }

  std::vector<T>::iterator begin()
  {
    return mVector.begin();
  }

  std::vector<T>::iterator end()
  {
    return mVector.end();
  }

  std::vector<T>::iterator find(const T& value)
  {

  }

  const T& left()
  {
    assert(mVector.size() != 0);
    return mVector[0];
  }

  const T& right()
  {
    assert(mVector.size() != 0);
    return mVector[mVector.size() - 1];
  }

private:
  std::vector<T> mVector;
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
      vector<T> vec;
      vec.push_back();
      mList.push_back()
    }


  }

  bool has(const T& value)
  {

  }

private:
  std::list< sorted_vector<T> > mList;
};