#ifndef LABMODE_H
#define LABMODE_H
/* A derivation of SimoN.
Intended usage:
  For normal operation of your system, you would derive from SimoN. However, during
  development, if you derive from LabMode (with the same structure) you inherit
  useful procedures to characterize your system:
  - Monitor (read Amp consumption while on etc...)
  - Real Time support (how long each step in the control loop takes)

It assumes/needs:
  - The actuator has a stable dynamics.
  - You have to implement steadyState();
  - You have implemented the sensor acquisition scheme (as you will use it in the final configuration)

NB: You need to modify the contstructor too.
 However, it saves a bit of memory when you deploy deriving from SimoN.
*/
#include "simoN.h"
/*#include "../sensors/sensor.h"
#include "../actuators/actuator.h"
#include "../units/units.h"
#include "../algebra/algebra.h"
#include "../rStack/rStack.h"
#include "../../include/statistic/sAnalysis.h"*/

template<int nSensors,
         int stateSize,
         int nStateTimeRec   = 2,
         int nMeasureTimeRec = 2>
class LabMode: public SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec> {
public:
  using stateType = Gmatrix<stateSize,1,dataL>;
  using measureType = Gmatrix<nSensors,1,dataL>;
  using controlInputType = float;
  using timeType = int;
  //Public data
  LabMode(){};
  LabMode(Actuator& a, Sensor* vec [nSensors]);
  LabMode(const LabMode &) = default;
  LabMode& operator=(const LabMode&) = default;
  // High level
  void    dynCharacterization(); //Not const because I change measures
  void staticCharacterization(unsigned int nTest,int nMeasures,int maxTimeOutS=5);
  void     rtCharacterization() const;
  //low level
  virtual bool steadyState() const =0;
  void printSensInfo()   const;
  void printMeasure() const;
};

//===========================0 Implementations 0================================
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::LabMode(Actuator& a, Sensor* vec [nSensors] ): SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>(a,vec){};

//------------ Implementation of HIGH LEVEL methods
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::dynCharacterization() {};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::staticCharacterization(unsigned int nTest,int nMeasures,int maxTimeOutS) {
//Takes several (=nMeasures) measures in many (=nTest) steady state conditions.
bool timeout = false;
float command = 0;
float deltaCommand = ( act->inputMax() - act->inputMin() )/nTest;
//Serial.println(" Static Characterization ");
act->command(act->inputMin()); //start the actuator
//Serial.print("Command: "); Serial.println( act->inputMin() );
printSensInfo();
while (!steadyState()){
  getNewMeasure();
  estimateState();
  print2terminal("Waiting for stead state");
  delay(500);
  //add timeOut;
  }
  for (int test=1; test <= (int) nTest; test++){  //In steady state, ready to begin a new test
    command = act->inputMin() + test*deltaCommand;
    act->command(command);
    //Serial.print("Command: "); Serial.println( act->inputMin() );
    printSensInfo();
    while (!steadyState()){
      getNewMeasure();
      estimateState();
      print2terminal("Waiting for stead state");
      delay(500);
    }; //wait for steady state,
    for(int read = 0; read<nMeasures ;read++){
      getNewMeasure();
       printMeasure();
    }
    //move to next test
  }
};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::printSensInfo() const{
  string tab = " \t ";
  string nl  = " \n ";
  string val = "val";
  string error  = "err";
  print2terminal("T[ms] ");
  for (int i=0; i < nSensors ; ++i){
    print2terminal(sensorV[i]->id());
    print2terminal(tab);
    print2terminal(sensorV[i]->unit());
    print2terminal(tab);
  }
  print2terminal(nl);
  print2terminal(tab);
  for (int i=0; i < nSensors ; ++i){
    print2terminal(val);
    print2terminal(tab);
    print2terminal(error);
    print2terminal(tab);
  }
  print2terminal(nl);
};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::printMeasure() const{
  string tab = " \t ";
  string nl  = " \n ";
  print2terminal(timeStamp[0]);
  print2terminal(tab);
  for (int i=0; i < nSensors ; ++i){
    print2terminal(measure[0](i).value );
    print2terminal(tab);
    print2terminal(measure[0](i).error );
    print2terminal(tab);
  }
  print2terminal(nl);
};


#endif
