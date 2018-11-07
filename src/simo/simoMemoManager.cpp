#include "../../include/simo/simo.h"
#include "../../include/units/units.h"
#include "../../include/sensors/sensor.h"
#include "../../include/minimalInterface/minInterface.h"
#include "../../include/statistic/statistic.h"
#include <vector>
using namespace std;

SimoMemoManager::SimoMemoManager(Actuator & MainAct, Sensor & MainSensor):
  act(MainAct),
  sensorV({& MainSensor}),
  measureA({}),
  measureB({}),
  currentMeasurament( & measureB),
  prevMeasurament( & measureA),
  state({data(0,0)}),
  lastInput(0.0),
  targetState(0.0){}

void SimoMemoManager::addSensor( Sensor & newSensor){
  sensorV.push_back( &newSensor);
}

const Sensor& SimoMemoManager::sensorN(unsigned int n){
  if (n <= sensorV.size()-1)
    return *sensorV[n];
  else
    return *sensorV[sensorV.size()-1];
}

const vector<data>&  SimoMemoManager::readMultipleSensors(const vector<Sensor*> & SensorRead, int n){
//reads the sensor you provide and updates state
  vector<data>* Measurament2Rewrite = prevMeasurament;
  int n_sensors = SensorRead.size();
  int n_readout = n;
  //unsigned long t_start,t_end;
  //float duration_ms;
  vector< vector<data> > matrixRes(n_sensors);
  for ( int i = 0 ; i < n_sensors ; i++ ) //preallocation for speed
     matrixRes[i].resize(n_readout);

  //t_start = timeMicro();
  for(int n_read = 0; n_read < n_readout; ++n_read){
    for (int i_sensor=0; i_sensor< n_sensors; ++i_sensor){  //Read multiple times
      matrixRes[i_sensor][n_read] = SensorRead[i_sensor]->readRaw();
    }
  }
  //t_end = timeMicro();
  //duration_ms = 1.0*(t_end-t_start) / 1000.0;

  data mean_value, std_value, worst_case;
  for(int i_sensor=0; i_sensor < n_sensors ; ++i_sensor){
      mean_value = mean( matrixRes[i_sensor] );
      std_value  = standardDev( matrixRes[i_sensor], mean_value);
      worst_case = data(mean_value.value, std_value.value+mean_value.error);
      (*Measurament2Rewrite)[i_sensor] = SensorRead[i_sensor]->interpret(worst_case);
  }

  prevMeasurament = currentMeasurament; //is a reassignment of the reference OR a copy of content?
  currentMeasurament = Measurament2Rewrite;
  return currentMeasure();
}

const vector<data>& SimoMemoManager::currentMeasure() const{
  return (*currentMeasurament);
}

const vector<data>& SimoMemoManager::prevMeasure() const{
  return (*prevMeasurament);
}

void SimoMemoManager::updateState(const vector<data>& newState){
  // saves the state vector onto memory
  state = newState;
}

const vector<data>& SimoMemoManager::currentState() const{
  //protected access to state
  return state;
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
