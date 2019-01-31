#ifndef CYCLICMEMO_H
#define CYCLICMEMO_H
/*  Cyclic memory is a finite record of the previous N steps in a series.
    It models a time series which can be accessed by relative index
    (most recent data-> idx = 0, the previous one-> idx =-1, 2 time step ago idx =-2 etc).
    Features:
        -Insert and read are in constant time.
        -Data are protected and can not modified once they are added.
        -If idx is out of bound (too much in the past or in the future)
         best approximation is provided (idx < -N => idx = -N)
        -Container friendly features such as empty() and size();
*/
#include <iostream>
#include <cmath>

template<class T,int n=2>
class Record{
private:
  T buffer[n];
  unsigned int start;
  unsigned int sizeInt;
public:
  Record():start(0),sizeInt(0){};

  void push(const T& toInsert ){
           start = (start + 1) % n;
           if (sizeInt<n) ++sizeInt;
           buffer[start] = toInsert;
    }

  const T& read(int idx) const{
    if (idx > 0) idx = 0;
    int maxHistory = -std::min((int)sizeInt,n)+1;
    if (idx < maxHistory) idx = maxHistory;
    idx = (start+idx+n) % n;
    return buffer[idx];
  }

  const T& operator[](int idx) const{
    return read(idx);
  }

  unsigned int size(){
    return sizeInt;
  }

  bool empty(){
    if (sizeInt==0) return true;
    else return false;
  }
};


#endif
