#include "catch.hpp"
#include "../../include/units/units.h"
#include "../../include/sensors/currentS.h"
#include "../../include/actuators/esc.h"
#include "../../include/simo/simo.h"
//#include "../../include/minimalInterface/minInterface.h"

#include<iostream>
using namespace std;

CurrentS CS1(1,"cs");
CurrentS CS2(2,"cs2");
Esc rw(8);
SimoMemoManager simo(rw,CS1);

TEST_CASE("Simo memory management-names", "[basics]"){
  REQUIRE( simo.sensorN(0).id() == "cs");
  REQUIRE( simo.sensorN(1).id() == "cs");
  simo.addSensor(CS2);
  REQUIRE( simo.sensorN(1).id() == "cs2");
  REQUIRE( simo.target() == 0);
  simo.setTargetState(2);
  REQUIRE( simo.target() == 2.0);
  vector<data> state0(2,data(1,0) );
  REQUIRE( simo.currentState()[0] == data(0,0));
  simo.updateState(state0);
  REQUIRE( simo.currentState() == state0);
}

TEST_CASE("Simo memory management-read Multiple sensors", "[basics]"){
  vector<Sensor*> vSens;
  vSens.push_back(&CS1);

  simo.readMultipleSensors(vSens);
  REQUIRE(simo.currentMeasure().size() == 1 );
  vSens.push_back(&CS2);
  simo.readMultipleSensors(vSens);
  REQUIRE(simo.currentMeasure().size() == 2 );
  REQUIRE(simo.prevMeasure().size() == 1 );
  //cout << "currentM size " << simo.currentMeasure().size() << endl;
  //cout << "prevM size " << simo.prevMeasure().size() << endl;
}

TEST_CASE("Simo memory management-measuraments handling", "[basics]"){
}

TEST_CASE("Simo memory management-control inputs handling", "[basics]"){
}

TEST_CASE("Simo memory management-state record handling", "[basics]"){
}
