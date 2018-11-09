#ifndef SIMOMEMOMANAGER_H
#define SIMOMEMOMANAGER_H
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

  unsigned long int timeA; // in milliseconds
  unsigned long int timeB;

  unsigned long int* timeCurrent; // in milliseconds
  unsigned long int* timePrev;

  vector<data> state;
  float lastInput;
  vector<data> targetState;
public:
  SimoMemoManager(Actuator &, Sensor &);
  void addSensor(Sensor &);
  const Sensor& sensorN(unsigned int) const; //protected access to sensor #N
  const vector<Sensor*> & attachedSensors() const;

  const vector<data>& readMultipleSensors(int = 5); //reads all sensor assigned to SimoMemo
  const vector<data>& readMultipleSensors(const vector<Sensor*> &, int = 5); //reads the sensor you provide and updates state
  //!!! WARNGING!!!! no checks on vector of sensors... so it is risky, do not use

  const vector<data>& currentMeasure() const; //Read only this references get updated when all sensors are read
  const vector<data>& prevMeasure() const;

  const unsigned long int & timestampCurrentMeasure() const; //Read only this references get updated when all sensors are read
  const unsigned long int & timestampPrevMeasure() const;

  void updateState(const vector<data>&); // saves the state vector onto memory
  const vector<data>& currentState() const; //protected access to state

  bool applyControlInput( float ); //has direct acess to the hardware and updates "lastInput"
  const float & lastAppliedInput() const;

  void setTargetState(const vector<data> &);
  const vector<data>& target() const;  //protected access to targetState
};
#endif
