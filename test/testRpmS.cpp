#include "catch.hpp"
#include "../../include/units/units.h"
#include "../../include/sensors/rpmS.h"

RpmS rpmS(1,"rpm_s");

TEST_CASE("RPM Sensor", "[basics]"){
  REQUIRE(rpmS.id() == "rpm_s");
  REQUIRE(rpmS.unit() == "rpm");
}

TEST_CASE("RPM Sensor interpret law", "[basics]"){
  REQUIRE(rpmS.interpret(15000).value == 1000 ); //mid value
  REQUIRE(rpmS.interpret(10000).value == 1500 );
  REQUIRE(rpmS.interpret( 1000).value == 15000);
  REQUIRE(rpmS.interpret(    0).value == 0    );
}

TEST_CASE("RPM Sensor error propagation","[intermediate]"){ //these are a bit weird
  REQUIRE(rpmS.interpret( data(15000,10) ).error == 0 );
  REQUIRE(rpmS.interpret( data(10000,10) ).error == 1 );
  REQUIRE(rpmS.interpret( data( 1000,10) ).error == 146 );
}
