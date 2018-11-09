//More indepth tests for type "data"
#include "../../include/catch.hpp"
#include "../../include/units/units.h"
//#include "../../include/minimalInterface/minInterface.h"
#include <cmath>

//Set up for the whole test suite
data aData(100,10);
data bData(10,1);
data cData(10,0);
data dData(100,1);

TEST_CASE("Units2: arithmetic division","[basics]"){
  REQUIRE( (aData+1).isIdenticalTo(data(101,10)));
  REQUIRE( (aData / 2).isIdenticalTo(data(50,5)));
  REQUIRE( (aData / 10).isIdenticalTo(data(10,1)));
  REQUIRE( (aData / bData).isIdenticalTo(data(10,1)));
  REQUIRE( (cData / 10).isIdenticalTo(data(1,0)) );
  REQUIRE( (dData / 2).isIdenticalTo(data(50,0)) );
}

TEST_CASE("Units2: arithmetic division2","[basics]"){
  REQUIRE( 1000 / aData == data(10,5) );
  REQUIRE( 1000 / bData == data(100,1) );
  REQUIRE( 1000 / cData  == data(100,1) );
}

TEST_CASE("Units2: check the zero value ","[basics]"){
  aData = 0;
  unsigned int n = 3;
  REQUIRE( (0/3) == data(0,0) );
  REQUIRE( (aData/(n-1))  == data(0,0) );
  REQUIRE( sqrt(aData / (n-1))  == data(0,0) );
}

TEST_CASE("Units2: check pow function ","[basics]"){
  aData = 10;
  int n = 0;
  REQUIRE( pow(10,0)      == 1 );
  REQUIRE( pow(aData,n)   == 1 );
  REQUIRE( pow(aData,0.0) == 1 );
}
