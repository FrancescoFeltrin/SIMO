#include "../../include/statistic/sAnalysis.h"
#include "../../include/minimalInterface/minInterface.h"

#ifdef CPU_ARCH
  #include <cmath>
#endif
#ifdef ARDUINO_ARCH
  #include <math.h>
#endif

dataL sAnalysis(const data array[],unsigned int aSize){
  //need to compute mean and std
  float sum = 0; // float don't likely overflow have a max @ 3*E+38
  float avg = 0;
  float std = 0;
  for (unsigned int i = 0; i < aSize; ++i)
    sum = sum + array[i].value;
  avg = sum/aSize;
  sum =  0;
  if ( aSize > 2 ){
    for (unsigned int i=0; i < aSize; ++i)
      sum = sum + pow( array[i].value-avg ,2);
    std = sqrt( sum / ( aSize-1 ) );
    }
  else if(aSize == 2 )
    std = (array[0].value-array[1].value)/2;
  else //aSize = 1 or 0
    std = array[0].error ;
  //you could check if the avg and std are compatible with the error margins...
  return dataL(avg,std);
}

/*
T mean(const T array [],unsigned int aSize){
  T sum = 0;
  for (unsigned int i = 0; i < aSize; ++i){
    sum = sum + array[i];
  }
  sum = sum / aSize;
  return sum;
}

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
*/
