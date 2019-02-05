#include "catch.hpp"
#include "../../include/simo/simoN.h"

//#include "../../include/units/units.h"

#include "../../include/sensors/sensor.h"
#include "../../include/sensors/currentS.h"
#include "../../include/actuators/esc.h"
#include "../../include/minimalInterface/minInterface.h"



#include<iostream>
//using namespace std;

CurrentS cs1(1,"cs");
CurrentS cs2(2,"cs2");
Esc Rw(8);

Sensor* senV[2] = {&cs1, &cs2};
SimoN<2,2> test1(Rw,senV);

TEST_CASE("SimoN initialization", "[basics]"){
  test1.getNewMeasure();
  test1.computeControlInput();
  test1.applyControlInput();
  REQUIRE(1==1);
}

/*TEST_CASE("Simo memory management-read Multiple sensors", "[basics]"){
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
}*/
