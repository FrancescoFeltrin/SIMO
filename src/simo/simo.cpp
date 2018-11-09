#include "../../include/simo/simo.h"
#include "../../include/units/units.h"
#include "../../include/sensors/sensor.h"
#include "../../include/minimalInterface/minInterface.h"
//#include "../../include/statistic/statistic.h"

/*    Single (control) input, Multiple Output
This is a high level class to implement a general control scheme. Its goal is:
  - hide all the boring memory management routines (in SimoMemoManager)
  - present a clear interface to improve re usability of the code.

*/

Simo::Simo(Actuator & output, Sensor & mainSensor): SimoMemoManager(output, mainSensor) {}

const vector<data>& Simo::getMeasuraments(){
    //base line, reads all sensors and lets SimoMemoManager deal with everything
    return readMultipleSensors(5);
    // BUT, if you want you could read only some of the sensors, maybe because you know
    // one to be broken.
}

void  Simo::estimateTrueState(){
// first computes what it should read from sensors
  unsigned int deltaTms = timestampCurrentMeasure()-timestampPrevMeasure();
  vector<data> Estimatedstate = integrateStateEq(currentState(),deltaTms);
  vector<data> EstimatedMeasure = observeState(Estimatedstate);
  //compares it with what it actually measured
  checkForFailureSigns(Estimatedstate); // <- this might raise warning flags
  // then you actually use past and present measuraments to estimate state.
  vector<data> bestEstimate = stateObserver();
  updateState(bestEstimate);
}

float Simo::computeControlInput() const{
  return computeControlInput(target());
}

float Simo::computeControlInput(const vector<data> & targetState) const{
  //example Proportional control
  int k = 10;
  float u = k*(currentState()[0]-targetState[0]).value;
  return u;
}

vector<data> Simo::integrateStateEq(const vector<data>& state,const unsigned int & Dt_ms) const {
  //need to implement state equation
  vector<data> openLoopState;
  openLoopState.push_back(state[0]+Dt_ms*lastAppliedInput());
  return openLoopState;
}

vector<data> Simo::Simo::observeState(const vector<data> & state) const{
  //returns expected measurements
  vector<data> expectedMeasure;
  expectedMeasure = state;
  return expectedMeasure;
}

vector<data> Simo::stateObserver() const {
  //Do whatever you need to estimate the state from measuraments
  return currentState(); //to change !
}

void Simo::checkForFailureSigns(const vector<data> & expectedMeasure){
  //apply control input comes from above
  if (currentMeasure() != expectedMeasure){
    print2log(" Anomaly detected \n ");
  }
}

bool Simo::functionalTest(){
  return true;
}
