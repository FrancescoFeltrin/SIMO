#include "../../include/simo/simo.h"
#include "../../include/simo/brushless.h"
#include "../../include/units/units.h"
#include "../../include/sensors/sensor.h"
#include "../../include/minimalInterface/minInterface.h"

Brushless::Brushless(Esc & esc, RpmS & rpm, CurrentS & cs):Simo_lab(esc,rpm) {
  addSensor(cs);
}

float Brushless::computeControlInput(const vector<data> & targetState) const{
  int wantedRPM = targetState[0].value;
  float a = -9.8005;
  float b = 607.1753;
  float c1 = 650.7964;
  float commandGuess1 = (-b+sqrt(pow(b,2)-4.0*a*(c1-wantedRPM) ) )/2.0/a;
  float commandGuess2 = (-b-sqrt(pow(b,2)-4.0*a*(c1-wantedRPM) ) )/2.0/a;
  float commandMin = min(commandGuess1,commandGuess2);
  return commandMin;
}

vector<data> Brushless::integrateStateEq(const vector<data>& state,const unsigned int & Dt_ms) const{
  // Try to guess the future state based on input and time
  vector<data> propagatedState(2,data(0,0));
  float command100 = lastAppliedInput(); // 100%
  float a  =  -9.8005;
  float b  = 607.1753;
  float c1 = 650.7964;
  float RPM = a*pow(command100,2)+b*command100+c1;
  data rpmMes = state[0];
  unsigned int error = abs((rpmMes.value-RPM)/(1 + Dt_ms/5000));
  propagatedState[0] = data(RPM,error);
  propagatedState[1] = data(250,150); //RPM/s

  return propagatedState;
}

vector<data> Brushless::observeState(const vector<data> & state) const{
  //returns expected measurements
  vector<data> expectedMeasure(2,data(0,0));
  data rpmEst = state[0];
  data mAmpEst = (rpmEst / 4000)*150 + 116; //from datasheet
  mAmpEst.error = mAmpEst.error+ mAmpEst.value*0.1; //10 % error
  expectedMeasure[0] = rpmEst;
  expectedMeasure[1] = mAmpEst; // mA
  return expectedMeasure;
}

vector<data> Brushless::stateObserver() const{
  //Do whatever you need to estimate the state from measuraments
  unsigned int ms = timestampCurrentMeasure()-timestampPrevMeasure();
  vector<data> state(2,data(0,0));
  state[0] = currentMeasure()[0]; //-> rpm
  state[1] = (currentMeasure()[0]-prevMeasure()[0])/ms*1000; //-> rpm/s
  return state;
}

void Brushless::checkForFailureSigns(const vector<data> & expectedMeasure){
  data mAmpRead = currentMeasure()[1];
  data mAmpExp = expectedMeasure[1];
  if (mAmpRead-mAmpExp > 500){
    print2log(" Anomaly detected: Exp current");
    print2log(mAmpExp.value);
    print2log(" mAmp. Measured: ");
    print2log(mAmpRead.value);
    //applyControlInput( 0 ); //stop everything
  }
}
