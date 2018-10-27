#include <iostream>
#include <vector>
//#include <ArduinoSTL.h> //Arduino version of STL
//#include "../../../ArduinoSTL-1.1.0/src/ArduinoSTL.h" //For test
#include "../../include/statistic/statistic.h"
#include<iostream>

using namespace std;
int main()
{
  vector<int> basevec {5,6,5,6,5,6,5,6,5,6,5,6,5,6,50};
  float vecMean = 2.0;
  float vecSTD;
  vecMean = mean(&basevec);
  //for (int i=0; i<basevec.size(); ++i)
  //cout<<basevec[i]<<'\n';
  vecSTD = standardDev(&basevec);
  cout<< vecMean<<'\n';
  cout<< vecSTD<<'\n';

  vector<int> outputFilter;
  outputFilter= filterOutliers( &basevec);
  for (unsigned int i=0; i<outputFilter.size(); ++i)
    cout<<basevec[i]<<'\n';

  cout<<"New mean "<< mean(&outputFilter) <<'\n';
  cout<<"New STD " << standardDev(&outputFilter) <<'\n';
}
