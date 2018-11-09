#include "../../include/simo/simo.h"
#include "../../include/units/units.h"
#include "../../include/sensors/sensor.h"
#include "../../include/minimalInterface/minInterface.h"
#include "../../include/statistic/statistic.h"
// To do:
// -Add checks on which sensor you can read. Read Multiple Sensor should only allow
// a subset of the assigned sensor. This way you trust what you are reading.

#include <vector>
using namespace std;

SimoMemoManager::SimoMemoManager(Actuator & MainAct, Sensor & MainSensor):
  act(MainAct),
  sensorV({& MainSensor}),
  measureA(vector<data>(1,data(0.0)) ),
  measureB(vector<data>(1,data(0.0)) ),
  currentMeasurament( & measureA),
  prevMeasurament( & measureB),
  timeA(0),
  timeB(0),
  timeCurrent(& timeA),
  timePrev(& timeB),
  state({data(0,0)}),
  lastInput(0),
  targetState(0) {}

void SimoMemoManager::addSensor( Sensor & newSensor){
  sensorV.push_back( &newSensor);
}

const Sensor& SimoMemoManager::sensorN(unsigned int n) const{
  if (n <= sensorV.size()-1)
    return *sensorV[n];
  else
    return *sensorV[sensorV.size()-1];
}

const vector<Sensor*> & SimoMemoManager::attachedSensors() const{
  return sensorV;
}

const vector<data>&  SimoMemoManager::readMultipleSensors(const vector<Sensor*> & Sensor2Read, int n){
  //reads multiple sensors at the "same" time, updates measuraments records (which include time of measure).
  int n_sensors = Sensor2Read.size();
  int n_readout = n;
  vector<data>  recordedMeasures(n_sensors,data(0,0));
  vector< vector<data> > matrixRes(n_sensors);

  vector<data>* Measurament2Rewrite = prevMeasurament;
  prevMeasurament = currentMeasurament; // The last measure is now SEEN as the previous measure
  currentMeasurament = Measurament2Rewrite; //points to previous measurement

  unsigned long int* time2Rewrite = timePrev; //as for measurements, so for timestamps
  timePrev = timeCurrent;
  timeCurrent = time2Rewrite;

  unsigned long int tStart,tEnd,timeStamp;

  for ( int i = 0 ; i < n_sensors ; i++ ) //preallocation for speed
     matrixRes[i].resize(n_readout);
  tStart = timeMicro();
  for(int n_read = 0; n_read < n_readout; ++n_read){
    for (int i_sensor=0; i_sensor< n_sensors; ++i_sensor){  //Read multiple times
      matrixRes[i_sensor][n_read] = Sensor2Read[i_sensor]->readRaw();
    }
  }
  tEnd = timeMicro();
  timeStamp = tStart + (tEnd-tStart)/2; // putting a timestamp in the middle of the measure
  (*timeCurrent) = timeStamp/1000; //ms

  //needs to check where you are saving the data!

  data mean_value, std_value, worst_case;
  for(int i_sensor=0; i_sensor < n_sensors ; ++i_sensor){
      mean_value = mean( matrixRes[i_sensor] );
      std_value  = standardDev( matrixRes[i_sensor], mean_value);
      worst_case = data(mean_value.value, std_value.value+mean_value.error);
      recordedMeasures[i_sensor] = Sensor2Read[i_sensor]->interpret(worst_case);
  }
  *currentMeasurament = recordedMeasures; // this could be measureA or B.
  return currentMeasure();
}

const vector<data>&  SimoMemoManager::readMultipleSensors(int n){
  return readMultipleSensors(sensorV,n);
}

const vector<data>& SimoMemoManager::currentMeasure() const{
  return (*currentMeasurament);
}

const vector<data>& SimoMemoManager::prevMeasure() const{
  return (*prevMeasurament);
}

const unsigned long int & SimoMemoManager::timestampCurrentMeasure() const{
  return (*timeCurrent);
}

const unsigned long int & SimoMemoManager::timestampPrevMeasure() const{
    return (*timePrev);
}

void SimoMemoManager::updateState(const vector<data>& newState){
  // saves the state vector onto memory
  state = newState;
}

const vector<data>& SimoMemoManager::currentState() const{
  return state;  //protected access to state
}

bool SimoMemoManager::applyControlInput( float controlInput ){
  //has direct acess to the hardware and updates "lastInput"
  act.command(controlInput);
  lastInput = controlInput;
  return true;
}

void SimoMemoManager::setTargetState(float target){
  targetState = target;
}

const float&  SimoMemoManager::target() const{
  //protected access to targetState
  return targetState;
}
