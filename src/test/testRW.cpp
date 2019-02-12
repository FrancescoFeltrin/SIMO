#include "catch.hpp"
#include "../../include/simo/RW.h"

#include "../../include/sensors/currentS.h"
#include "../../include/sensors/rpmS.h"
#include "../../include/actuators/esc.h"
//#include "../../include/minimalInterface/minInterface.h"

#include<iostream>
using namespace std;

RpmS rpms1(1,"rpm1");
CurrentS cs_1(2,"cs1");
Esc rwA(8);

Sensor* senV1[2] = {&rpms1, &cs_1};
Sensor* senV2[2] = {&cs_1, &rpms1};
RW testA(rwA,senV1);
RW test2(rwA,senV2);

TEST_CASE("RW initialization", "[basics]"){
  cout<<">>>>     Start RW test"<<endl;
  testA.getNewMeasure();
  testA.estimateState();
  testA.computeControlInput();
  testA.applyControlInput();
  REQUIRE(1 == 1);
  cout<<"<<<<     End RW Test"<<endl;
  //test1.readAllSensors(5);
}

TEST_CASE("RW - Test basic functions ", "[basics]"){
  //do they behave as expected with errors?
  REQUIRE( testA.rpm2Pwm(6000)  == dataL(10.6,1 ) );
  REQUIRE( testA.mAmp2Rpm(dataL(150,20) )  == dataL(5500,50) );
  REQUIRE( testA.rpm2mAmp(dataL(5500,10)) == dataL(150,10 ) );
}
