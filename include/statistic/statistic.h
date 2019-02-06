/* Basic statistical functions based on C array (to avoid dyanamic allocation)
 or on std::vector using templates.
 To do:
  -Include overflow protection
*/
#ifndef STATISTIC_H
#define STATISTIC_H

#include <cmath>

template<class T>
T mean(const T array [],unsigned int aSize){
  T sum = 0;
  for (unsigned int i = 0; i < aSize; ++i){
    sum = sum + array[i];
  }
  sum = sum / aSize;
  return sum;
}

template<class T>
T standardDev(const T array[],unsigned int aSize, const T & avg){
  T std = 0;
  if ( aSize > 2 ){
    T sum = 0;
    for (unsigned int i=0; i < aSize; ++i){
      sum = sum + pow( array[i]-avg ,2);
    }
    std = sqrt( sum / ( aSize-1 ) );
    }
  else if(aSize == 2 )
    std = (array[0]-array[1])/2;
  else //aSize = 1 or 0
    std = 0 ;
  return std;
}

template<class T>
T standardDev(const T array [],unsigned int aSize){
  T avg = mean(array,aSize);
  return standardDev(array,aSize,avg);
}

//=========== With STD vectors ============================
#include <vector>
//#include <ArduinoSTL.h> //Arduino version of STL // For the arduino
using namespace std;

template<class T>
T mean(const vector<T> &  vector){
  T sum = 0;
  unsigned int n = vector.size();
  for (unsigned int i = 0; i < n; ++i){
    sum = sum + vector[i];
  }
  sum = sum / n;
  return sum;
}

template<class T>
T standardDev(const vector<T> & vector, const T & avg){
  unsigned int n = vector.size();
  T std = 0;
  if ( n > 2 ){
    T sum = 0;
    for (unsigned int i=0; i < n; ++i){
      sum = sum + pow( vector[i]-avg ,2);
    }
    std = sqrt( sum / ( n-1 ) );
    }
  else
    std = (vector[0]-vector[1])/2;
  return std;
}

template<class T>
T standardDev(const vector<T> & vector){
  T avg = mean(vector);
  return standardDev(vector,avg);
}

/*
vector<int> filterOutliers(vector<int>* inputV);
vector<int> filterOutliers(vector<int>* inputV, float meanValue, float std);*/


//maybe also linear and quadratic regression?

#endif
