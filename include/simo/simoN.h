#ifndef SIMON_H
#define SIMON_H

/* A better version of simo.h.
ALL TEMPLATE
Improvements:
  - Memory/record of previous timestep is stored and protected with cyclicMemory
  - No dynamic allocation-> no std library maybe
  - Minimal interfaces
To do:
  - Test
*/
#include "../sensors/sensor.h"
#include "../actuators/actuator.h"
#include "../units/units.h"
#include "../algebra/algebra.h"
#include "../cyclicMemory/cyclicMemory.h"

#include <iostream>
using namespace std;

template<int nSensors,
         int stateSize,
         int nStateTimeRec   = 2,
         int nMeasureTimeRec = 2>class SimoN {
private:
  //Stuff to make it easier to read
  using stateType = Gmatrix<stateSize,1,dataL>;
  using measureType = Gmatrix<nSensors,1,dataL>;
  using controlInputType = float;
  using timeType = int;

  Actuator& act;
  Sensor* sensorV[nSensors];

public:
  //Public data
  Record <stateType  , nStateTimeRec   > state;
  Record <measureType, nMeasureTimeRec > measure;
  Record <timeType   , nMeasureTimeRec > timeStamp;
  Record <float      , nMeasureTimeRec > controlInput;
  controlInputType nextControl;
  stateType targetState;

  SimoN(){};
  SimoN(Actuator& a, Sensor* vec [nSensors] );

  //control functions (HIGH LEVEL).
  virtual void getNewMeasure();
  //virtual void estimateState() =0;
  virtual void computeControlInput();
  void applyControlInput(); //applies it and records the event

  //Lower level functions
  measureType readAllSensors(int nTimes= 3);
  //virtual stateType integrateStateEq(stateType s0,controlInputType u0,timeType deltaT) const =0;
  //virtual measureType observationModel(stateType s) const =0;
  //virtual controlInputType controlLaw(stateType state ,stateType target) const=0;
};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::SimoN(Actuator& a, Sensor* vec [nSensors] ): act(a){ //WTF! ,sensorV(vec){}; does not work
  for (int i=0; i<nSensors; ++i)
    sensorV[i] = vec[i];
  cout<<"SimoN constructor"<<endl;
}

//------------ Implementation of HIGH LEVEL methods
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::getNewMeasure(){
  Gmatrix<nSensors,1,dataL> newUpdate = readAllSensors();
  //if you want to check the inputs, do so now!
  measure.push(newUpdate); //commit to what you have measured
  cout<<"get New Measure done"<<endl;
}

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::computeControlInput(){
    //nextControl = controlLaw(state[0],targetState);
    cout<<" High level control input"<<endl;
}

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::applyControlInput(){
  act.command(nextControl);
  controlInput.push(nextControl);
  cout<<" contol input applied"<<endl;
}

//------------ Implementation of LOW LEVEL methods
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
Gmatrix<nSensors,1,dataL> SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::readAllSensors(int n){
  cout<<" read all sensors, n= "<< n<<endl;
  return measure[0];
};


#endif
