#include "catch.hpp"
#include "../../include/units/units.h"
#include "../../include/sensors/currentS.h"
//#include "../../include/minimalInterface/minInterface.h"

CurrentS CS(1,"cs");

TEST_CASE("Current Sensor", "[basics]"){
  REQUIRE(CS.minValue() == -20000);
  REQUIRE(CS.maxValue() == +20000);
  REQUIRE(CS.id() == "cs");
  REQUIRE(CS.unit() == "mA");
}

TEST_CASE("Current Sensor interpret law","[basics]"){
  REQUIRE(CS.interpret( 512 ) == 0 ); //mid value
  REQUIRE(CS.interpret( 200 ) == -15234);
  REQUIRE(CS.interpret( 800 ) == +14063);
}

TEST_CASE("Current Sensor error propagation","[intermediate]"){
  REQUIRE(CS.interpret( data(512,2) ).error == 98 );
  REQUIRE(CS.interpret( data(200,2) ).error == 98 );
  REQUIRE(CS.interpret( data(800,2) ).error == 98 );
}

TEST_CASE("Test read current Sensor ","[intermediate]"){
  REQUIRE(CS.read() == -586 );
}
