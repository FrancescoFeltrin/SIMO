//basic functions based on arrays of data
//For the moment, implementation and body together here


#include <vector>
//#include "../../../ArduinoSTL-1.1.0/src/ArduinoSTL.h" //For test
//#include <ArduinoSTL.h> //Arduino version of STL
#include <cmath>
//#include <Arduino.h>
//#include "../../../ArduinoHeader/Arduino.h"
#include "../../include/statistic/statistic.h"
#include <iostream>

using namespace std;

float mean(vector<int>* vecPtr){
  unsigned long sum = 0;
  int n = (*vecPtr).size();
  float average;
  bool overflow = false;
  for (int i=0; i< n; ++i){
    sum = sum + (*vecPtr)[i];
    if (sum > 4294967295 ){
      overflow = true;
      i = n + 1;
      //Serial.println();
      //Serial.println("WARNING! MEAN OVERFLOW");
      cout<<"Warning! Mean overflow";
      }
  }
  average = sum *1.0 / n;

  if (overflow == true){
    average = 0.0;
    for (int i=0; i< n; ++i)
      average = average + (*vecPtr)[i]*1.0 / n ;
  }
  return average;
}

float standardDev(vector<int>* vecPtr,float mean){
  float std = 0.0;
  float sum = 0.0;
  int n = (*vecPtr).size();
  bool overflow = false;

  for (unsigned int i=0; i< (*vecPtr).size();++i){
    sum = sum + pow( (*vecPtr)[i]-mean ,2);
    if (sum > 4294967295){
      overflow = true;
      i = n+1;
      //Serial.println();
      //Serial.println("WARNING! STD OVERFLOW");
      cout<<"Warning! Std overflow";
    }
  }
  std= sqrt(sum / ( vecPtr->size()-1.0 ) );
  if (overflow == true){
    sum  = 0;
    for (unsigned int i=0; i< (*vecPtr).size();++i){
      sum = sum + pow( (*vecPtr)[i]-mean ,2)* 1.0 /(n-1);
    }
    std = sqrt(sum);

  }
  return std;
}

float standardDev(vector<int>* inputV){
  float meanVal;
  float std=0;
  meanVal = mean(inputV);
  std = standardDev(inputV,meanVal);
  return std;
}


vector<int> filterOutliers(vector<int>* inputV,float meanValue,float std){
  //For now, I will assume outliers to be all the point ouside a Normal Dist
  //vector<int> normalized; //vector occupy a lot of space!
  int normValue;
  unsigned int n = (*inputV).size();
  float pm3Sigma = 0.0;
  for (unsigned int i=0; i < n; ++i){
    normValue = (int) ( ((*inputV)[i]-meanValue)/std)*10.0;
    //normalized.push_back(normValue);
    if (abs(normValue)>30){
      pm3Sigma++;
      /*Serial.println();
      Serial.print(" Abnormal: Mean 0 STD 1 ");
      Serial.print(" Value ");
      Serial.println(normValue*1.0 / 10.0, 2);*/
      cout<<" Abnormal: Mean 0 STD 1 Value "<<normValue*1.0 / 10.0;
      }
    }
    pm3Sigma = pm3Sigma * 100.0 / n;
    if (pm3Sigma > 0.3){
      vector<int> filterVec;
      //significant to filter but for now, just ignore...
      for (unsigned int i=0; i< n; ++i){
        normValue = (int) ( ((*inputV)[i]-meanValue)/std)*10.0;
        if (abs(normValue)<30)
          filterVec.push_back((*inputV)[i]);
      }
      return filterVec;
    }
    else
      return *inputV;
}

vector<int> filterOutliers(vector<int>* inputV){
  if ((*inputV).size() < 10)    //not enough data to be statistically sure
    return *inputV;
  else{
    float meanValue = mean(inputV);
    float std  = standardDev(inputV,meanValue);
    return filterOutliers(inputV, meanValue, std);
  }
}
