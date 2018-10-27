//basic functions based on arrays of data
//For the moment, implementation and body together here
#ifndef STATISTIC_H
#define STATISTIC_H

#include <vector>
//#include <ArduinoSTL.h> //Arduino version of STL // For the arduino
//#include "../../../ArduinoSTL-1.1.0/src/ArduinoSTL.h" //For test
#include <cmath>
using namespace std;

float mean(vector<int>* vecPtr);
float standardDev(vector<int>* vecPtr,float mean);
float standardDev(vector<int>* inputV);
vector<int> filterOutliers(vector<int>* inputV, float meanValue, float std);
vector<int> filterOutliers(vector<int>* inputV);

#endif
