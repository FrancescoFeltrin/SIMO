#include <vector>
//#include <ArduinoSTL.h> //Arduino version of STL
//#include "../../../ArduinoSTL-1.1.0/src/ArduinoSTL.h" //For test

#include "../../include/statistic/statistic.h"
#include "../../include/catch.hpp"

vector<int> TestVec {1,2,3,4,5,6,7,8,9,10};
vector<int>* vecp= &TestVec;
TEST_CASE("2: Test of statistic functions ","[statistic]"){
  REQUIRE( mean(TestVec) == 5 );
  REQUIRE( standardDev(TestVec) == 3);
}
