#include <vector>
#include "../../include/statistic/statistic.h"
#include "../../include/catch.hpp" //needed for testing

vector<int> TestVec {1,2,3,4,5,6,7,8,9,10};
TEST_CASE(" Statistic test -integer ","[basics]"){
  REQUIRE( mean(TestVec) == 5 );
  REQUIRE( standardDev(TestVec) == 3);
}

vector<float> TestVec2 {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
TEST_CASE(" Statistic test -float ","[basics]"){
  REQUIRE( mean(TestVec2) == 5.5 );
  REQUIRE( abs(standardDev(TestVec2)-3.027)< 0.001);
}
