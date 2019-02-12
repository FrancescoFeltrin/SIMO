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
#include "../rStack/rStack.h"
#include "../../include/statistic/statistic.h"

#include <iostream>
using namespace std;

template<int nSensors,
         int stateSize,
         int nStateTimeRec   = 2,
         int nMeasureTimeRec = 2> class SimoN {
private:
  //Stuff to make it easier to read
  Actuator* act;
  Sensor* sensorV[nSensors];
public:
  using stateType = Gmatrix<stateSize,1,dataL>;
  using measureType = Gmatrix<nSensors,1,dataL>;
  using controlInputType = float;
  using timeType = int;
  //Public data
  RStack <stateType  , nStateTimeRec   > state;
  RStack <measureType, nMeasureTimeRec > measure;
  RStack <timeType   , nMeasureTimeRec > timeStamp; //in milliseconds, when the sensor are read
  RStack <float      , nMeasureTimeRec > controlInput;
  controlInputType nextControl;
  stateType targetState;

  SimoN(){};
  SimoN(Actuator& a, Sensor* vec [nSensors] );
  SimoN(const SimoN &) = default;
  SimoN& operator=(const SimoN&) = default;

  //  control functions (HIGH LEVEL).
  virtual void getNewMeasure();
  virtual void estimateState() =0;
  virtual void computeControlInput();
  void applyControlInput(); //applies it and records the event

  //  Lower level functions
  measureType readAllSensors(int nTimes= 3);
  virtual stateType integrateStateEq(stateType s0,controlInputType u0,timeType deltaT) const =0;
  virtual measureType observationModel(stateType s) const =0;
  virtual controlInputType controlLaw(stateType state ,stateType target) const=0;
};

//===========================0 Implementations 0================================
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::SimoN(Actuator& a, Sensor* vec [nSensors] ): act(&a){
  for (int i=0; i<nSensors; ++i)
    sensorV[i] = vec[i];
  cout<<"SimoN constructor"<<endl;
}

//------------ Implementation of HIGH LEVEL methods
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::getNewMeasure(){
  using measureType = Gmatrix<nSensors,1,dataL>;
  measureType newUpdate = readAllSensors();
  //Example of Fault Detection in the sensor read
  /*measureType propagatedMeasure = observationModel(integrateStateEq(state(0),controlInput(0),0.1));
  if (newUpdate == propagatedMeasure){ //this check is performed at 3 sigma for each value
    measure.push(newUpdate); //commit to what you have measured
  }*/
  measure.push(newUpdate);
  cout<<"get New Measure done"<<endl;
}

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::computeControlInput(){
    nextControl = controlLaw(state[0],targetState);
    cout<<" High level control input"<<endl;
}

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::applyControlInput(){
  act->command(nextControl);
  controlInput.push(nextControl);
  cout<<" contol input applied"<<endl;
}

//------------ Implementation of LOW LEVEL methods
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
Gmatrix<nSensors,1,dataL> SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec>::readAllSensors(int n_readout){
  using measureType = Gmatrix<nSensors,1,dataL>;
  //Reads multiple sensors, one after the other,cycling n_readout times.
  //This way the "mean measurament" time is similar even with multiple read.

  data matrixRes[nSensors][n_readout];
  measureType recordedMeasures;
  unsigned long int tStart,tEnd,timeStamp0;

  tStart = timeMicro();
  for(int n_read = 0; n_read < n_readout; ++n_read){ //for n_readout times
    for (int i_sensor = 0; i_sensor< nSensors; ++i_sensor){  //Read all the sensors sensors
      matrixRes[i_sensor][n_read] = sensorV[i_sensor]->readRaw();
    }
  }
  tEnd = timeMicro();
  timeStamp0 = tStart + (tEnd-tStart)/2; // putting a timestamp in the middle of the measure
  timeStamp.push((timeType) timeStamp0/1000); //save the time of measurament in ms

  data mean_value, std_value, worst_case;
  dataL worstCaseF;
  for(int i_sensor=0; i_sensor < nSensors ; ++i_sensor){
      mean_value = mean( matrixRes[i_sensor],n_readout);
      std_value  = standardDev( matrixRes[i_sensor],n_readout, mean_value);
      worst_case = data(mean_value.value, std_value.value+mean_value.error);
      worst_case =  sensorV[i_sensor]->interpret(worst_case);
      worstCaseF = dataL((float) worst_case.value, (float) worst_case.error);
      recordedMeasures(i_sensor) = worstCaseF;
  }

  cout<<" read all sensors, n= "<< n_readout <<" timeStamp "<<timeStamp0 <<endl;
  return recordedMeasures;
}


#endif
