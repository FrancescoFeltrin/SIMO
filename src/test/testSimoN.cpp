#include "catch.hpp"
#include "../../include/simo/simoEx.h"

#include "../../include/sensors/sensor.h"
#include "../../include/sensors/currentS.h"
#include "../../include/actuators/esc.h"
#include "../../include/minimalInterface/minInterface.h"



#include<iostream>
using namespace std;

CurrentS cs1(1,"cs");
CurrentS cs2(2,"cs2");
Esc Rw(8);

Sensor* senV[2] = {&cs1, &cs2};
SimoEx test1(Rw,senV);

TEST_CASE("SimoEx initialization", "[basics]"){
  cout<<">>>>     Start simoEx test"<<endl;
  test1.getNewMeasure();
  test1.estimateState();
  test1.computeControlInput();
  test1.applyControlInput();
  REQUIRE(1==1);
  cout<<"<<<<     End SimoEx Test"<<endl;
  //test1.readAllSensors(5);
}

TEST_CASE("SimoEx -read Multiple sensors", "[basics]"){
  Gmatrix<2,1,dataL> ReadOut =  test1.readAllSensors(4);
  REQUIRE( ReadOut(0) == -586 );
  REQUIRE( ReadOut(1) == -586 );

  //REQUIRE(simo.currentMeasure().size() == 2 );
  //REQUIRE(simo.prevMeasure().size() == 1 );
  //cout << "currentM size " << simo.currentMeasure().size() << endl;
  //cout << "prevM size " << simo.prevMeasure().size() << endl;
}
/*
TEST_CASE("SimoEx -measuraments handling", "[basics]"){
}

TEST_CASE("SimoEx -control inputs handling", "[basics]"){
}

TEST_CASE("SimoEx -state record handling", "[basics]"){
}*/
