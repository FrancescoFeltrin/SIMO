#ifndef SIMO_H
#define SIMO_H
/* This is the interface for a Single Input Multiple Output system.
  At high level, it provides:
  - Controller basic functionalities (like state, last measurement, etc)
  - basic interfaces with outside world
  Since it relies on the previous step information, I want to provide protection to data.
  Therefore SIMO is derived from the SimoMemoManager class, which handles access to data.

  Compared to its derived classes, SIMO is minimal. This means that it does not
  have fancy features, to save memory.
*/

#include "../sensors/sensor.h"
#include "../actuators/actuator.h"
#include "../units/units.h"
#include "simoMemoManager.h"

#include <vector>
using namespace std;

class Simo: public SimoMemoManager{
public:
  Simo(Actuator &, Sensor &);
  virtual const vector<data>& getMeasuraments();  //High level command, that write uses readMultipleSensors
  virtual void  estimateTrueState();            //implements FDIR and a bunch of stuff
  virtual float computeControlInput() const;    //high level.
  virtual float computeControlInput(const vector<data> & targetState) const = 0;
  virtual vector<data> integrateStateEq(const vector<data>& state,const unsigned int & Dt_ms) const = 0;  //need to implement state equation
  virtual vector<data> observeState(const vector<data> & state) const  = 0; //returns expected measurements
  virtual vector<data> stateObserver() const = 0; //Do whatever you need to estimate the state from measuraments
  virtual void checkForFailureSigns(const vector<data> & expectedMeasure) = 0;
  //->apply control input comes from above
  virtual bool functionalTest() = 0; //return true is all is well
};

// This is for "in the lab characterization";
// Assumes that there is a human that reads the Serial.
class Simo_lab: public Simo {
public:
  Simo_lab(Actuator &, Sensor &);
  virtual void printCSVheader()  const;
  virtual void printAllMeasure() const;
  //virtual void staticCharact()   = 0;
  //virtual void dynamicCharact()  = 0;
  //virtual void performanceTest() = 0;
};

/* This is for "perpetual testing initiative"
class SimoPTI: public Simo_lab {
public:
  Simo3();
}; */


#endif
