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

template<int nSensors,
         int stateSize,
         int nStateTimeRec   = 2,
         int nMeasureTimeRec = 2>
class LabMode: public SimoN<nSensors, stateSize, nStateTimeRec, nMeasureTimeRec> {
public:
//  using stateType = Gmatrix<stateSize,1,dataL>;
//  using measureType = Gmatrix<nSensors,1,dataL>;
//  using controlInputType = float;
//  using timeType = long int;

  //Public data
  LabMode(){};
  LabMode(Actuator& a, Sensor* vec [nSensors]);
  LabMode(const LabMode &) = default;
  LabMode& operator=(const LabMode&) = default;
  // High level
  void    dynCharacterization(unsigned int nSteps=3,int nMin = 50, int maxTimeOutS = 10); //Not const because I change measures
  void staticCharacterization(unsigned int nSteps,int nMeasures,int maxTimeOutS=5);
  void     rtCharacterization() const;
  //low level
  virtual bool steadyState() const =0;
  void printSensInfo()   const;
  void printMeasure() const;
};

//=========================== Implementations ================================
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::LabMode(Actuator& a, Sensor* vec [nSensors] )
       :SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>(a,vec){};

//==========================  HIGH LEVEL   ======================
template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::dynCharacterization(
  unsigned int nSteps,int nMin,int maxTimeOutS) {
  // It jumps up and down between a set of points on the "output command" line
  // to attempt a complete characterization of the dynamics.
  // - nMin-> min measuraments per dynamic event
  // - maxTimeOutS -> how long to wait [s] before you move on
  //NB: The number of tests is nSteps*(nSteps-1)!^2, so a lot!

  float Commands[nSteps+1]; //jumps from one to all others
  using SimoN = SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>;
  long int timeout = 0;
  unsigned int t0;
  float   min = SimoN::SimoN::act->inputMin();
  float delta = ( SimoN::act->inputMax() - min )/nSteps;
  for(int i=0; i<=nSteps;i++){
    Commands[i] = min + i*delta;
  }
  print2terminal("\n Dynamic Characterization ");

  for(int start=0; start<nSteps; start++ ){
    timeout = 0;
    print2terminal("\n From "); print2terminal(Commands[start]); print2terminal(" ; \n");
    SimoN::nextControl = Commands[start];
    SimoN::applyControlInput();
    while (timeout < maxTimeOutS){   //wait for SS
        for (int i=0; i<nMin; i++){
          this->getNewMeasure();
          this->estimateState();
        }
        timeout = (SimoN::timeStamp[0] - t0)/1000000;
        print2terminal("Waiting for steady state ");
        //if (steadyState() == true)
        //   timeout = maxTimeOutS+1;
    }
    if (timeout > maxTimeOutS) print2terminal("-> Timeout");
    print2terminal("\n");

    for (int target =1; target<=nSteps-start;target++){
      timeout = 0;
      t0 = SimoN::timeStamp[0];
      print2terminal("\t to: "); print2terminal(Commands[start+target]);
      SimoN::nextControl = Commands[start+target];
      printSensInfo();
      SimoN::applyControlInput();
      while (timeout < maxTimeOutS){   //wait for SS
          for (int i=0; i<nMin; i++){
            this->getNewMeasure();
            this->estimateState();
            printMeasure();
          }
          timeout = (SimoN::timeStamp[0] - t0)/1000000;
          //print2terminal("\n \t Elapsed time[s]: ");
          //print2terminal(timeout);
          //if (steadyState() == true)
          //  timeout = maxTimeOutS+1;
      }
      //wait(2000);
      timeout = 0;
      t0 = SimoN::timeStamp[0];
      print2terminal("\t back to "); print2terminal(Commands[start]);
      SimoN::nextControl = Commands[start];
      printSensInfo();
      SimoN::applyControlInput();
      while (timeout < maxTimeOutS){   //wait for SS
          for (int i=0; i<nMin; i++){
            this->getNewMeasure();
            this->estimateState();
            printMeasure();
          }
          timeout = (SimoN::timeStamp[0] - t0)/1000000;
          //if (steadyState() == true)
          //  timeout = maxTimeOutS+1;
      }
      //wait(2000);
    }
  }
};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::staticCharacterization(
  unsigned int nSteps,int nMeasures,int maxTimeOutS){
//Takes several (=nMeasures) measures in many (=2*nSteps+1) steady state conditions.
//However, you want to characterize both going up (increasing levels) and down.
//Hence, twice as many tests.
  int timeout;
  using SimoN = SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>;
  float deltaCommand = ( SimoN::act->inputMax() - SimoN::act->inputMin() )/nSteps;
  print2terminal("\n Static Characterization \n ");

  SimoN::nextControl = SimoN::act->inputMin();
  SimoN::applyControlInput();
  wait(2000); //long delay to start

  for (int test=-nSteps; test <= (int) nSteps; test++){  //In steady state, ready to begin a new test
    timeout = 0;
    float command =  deltaCommand*nSteps - fabs(-test*deltaCommand);
    SimoN::nextControl = SimoN::act->inputMin() + command;
    SimoN::applyControlInput();
    print2terminal(" \n Command: "); print2terminal(SimoN::controlInput[0]);print2terminal("% \t");
    while (timeout < maxTimeOutS){
        print2terminal("Waiting for steady state ");
        for (int i=0; i<10; i++){
          this->getNewMeasure();
          this->estimateState();
          wait(1000);
          timeout+=1;
        }
        if (steadyState()== true)
          timeout = maxTimeOutS+13;
    }
    if (timeout == maxTimeOutS+13)
      print2terminal("-> Timeout");
    printSensInfo();
    for(int read = 0; read<nMeasures ;read++){
      this->getNewMeasure();
      printMeasure();
    }
  }
};

template<int nSensors,int stateSize,int nStateTimeRec,int nMeasureTimeRec>
void LabMode<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>::printSensInfo() const{
  using SimoN = SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>;
  string tab = " \t ";
  string nl  = " \n ";
  string val = "val";
  string error  = "err";
  print2terminal(nl);
  print2terminal("T [mus] \t");
  for (int i=0; i < nSensors ; ++i){
    print2terminal(SimoN::sensorV[i]->id());
    print2terminal(tab);
    print2terminal(SimoN::sensorV[i]->unit());
    print2terminal(tab);
  }
  print2terminal(nl);
  print2terminal("      \t");
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
  using SimoN = SimoN<nSensors,stateSize,nStateTimeRec,nMeasureTimeRec>;
  string tab = " \t ";
  string nl  = " \n ";
  print2terminal(SimoN::timeStamp[0]);
  print2terminal(" \t ");
  for (int i=0; i < nSensors ; ++i){
    print2terminal(SimoN::measure[0](i).value );
    print2terminal(tab);
    print2terminal(SimoN::measure[0](i).error );
    print2terminal(tab);
  }
  print2terminal(nl);
};


#endif
