/* Basic functions based on arrays of data
 Using template function.
 To do:
  -Include overflow protection
  -Does it make sense with units?
*/
#ifndef STATISTIC_H
#define STATISTIC_H

#include <vector>
//#include <ArduinoSTL.h> //Arduino version of STL // For the arduino
//#include "../../../ArduinoSTL-1.1.0/src/ArduinoSTL.h" //For test
#include <cmath>

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
  T std = 0;
  T sum = 0;
  unsigned int n = vector.size();
  for (unsigned int i=0; i < n; ++i){
    sum = sum + pow( vector[i]-avg ,2);
  }
  std = sqrt( sum / ( n-1 ) );
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
