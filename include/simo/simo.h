#ifndef SIMO_H
#define SIMO_H
/* This is the interface for a Single Input Multiple Output system.
  At high level, it provides:
  - Controller basic functionalities (like state, last measurement, etc)
  - basic interfaces with outside world
  Since it relies on the previous step information, I want to provide protection to data.
  Therefore SIMO is derived from the SimoMemoManager class, which handles access to data.

  SimoMemoManager:
  -

*/
#include "../sensors/sensor.h"
#include "../actuators/actuator.h"
#include "../units/units.h"

#include <vector>
using namespace std;

class SimoMemoManager {
private:
  Actuator& act;
  vector<Sensor*> sensorV;
  vector<data> measureA; //where the measureaments are stored
  vector<data> measureB;

  vector<data>* currentMeasurament;
  vector<data>* prevMeasurament;

  vector<data> state;
  float lastInput;
  float targetState;
public:
  SimoMemoManager(Actuator &, Sensor &);
  void addSensor(Sensor &);
  const Sensor& sensorN(unsigned int); //protected access to sensor #N

  const vector<data>& readMultipleSensors(const vector<Sensor*> &, int = 5); //reads the sensor you provide and updates state
  const vector<data>& currentMeasure() const; //Read only this references get updated when all sensors are read
  const vector<data>& prevMeasure() const;

  void updateState(const vector<data>&); // saves the state vector onto memory
  const vector<data>& currentState() const; //protected access to state

  bool applyControlInput( float ); //has direct acess to the hardware and updates "lastInput"

  void setTargetState(float);
  const float& target() const;  //protected access to targetState
};

/*
class Simo: public SimoMemoManager{
public:
  Simo(const Actuator &, const Sensor &);
  virtual vector<data>& readSensors();        //High level command, that write uses readMultipleSensors
  virtual void estimateState();               //process measurements and updates with best estimate of state
  virtual vector<data> stateFromMeasurments(const vector<data> &) = 0;
  virtual vector<data>& openLoopStateEstimate(); //using last input and last measurement
  virtual float computeControlInput() = 0;
  //apply control input comes from above
  virtual void  functionalTest() = 0;
  virtual void performanceTest() = 0;
}
*/

/* This is for "in the lab characterization"
class Simo2: public Simo {
public:
  Simo2();
  virtual void  staticCharact() = 0;
  virtual void dynamicCharact() = 0;
}; */

/* This is for "continuous testing"
class Simo3: public Simo {
public:
  Simo3();
  ?
}; */


#endif
