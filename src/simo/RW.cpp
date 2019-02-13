#include "../../include/simo/RW.h"
#include "../../include/sensors/rpmS.h"
#include "../../include/sensors/currentS.h"

/*NB: from the RW.h file
using stateType = Gmatrix<3,1,dataL>;   //State vector size = 3-> angular speed, angular acc, current (mAmp) drawn
using measureType = Gmatrix<2,1,dataL>; //Number of sensors = 2-> Rpm sensor + Amp sensor.
using controlInputType = float;
using timeType = int;
*/

RW::RW(){};

RW::RW(Actuator& a, Sensor* vec [2] ):SimoN<2,3,3,3>(a,vec){
  Sensor* S1 = vec[0];
  Sensor* S2 = vec[1];
  //check that the right order is respected
  if (dynamic_cast < RpmS* >(S1) ){
    if (dynamic_cast < CurrentS* >(S2) ){
        //SimoN(a,vec);
        //print2terminal("RW constructor to good end ");
    }
  }
  else{
    //print2terminal("Warning! Sensor list does not match expectations!->[rpm,current] ");
  }
};

void RW::estimateState(){
  //Get speed, acc and current from measuraments
  stateType currentState;
  timeType deltaT;
  if (timeStamp[0]>timeStamp[-1])
    deltaT = timeStamp[0]-timeStamp[-1];
  if (timeStamp[0]<=timeStamp[-1])
    deltaT = timeStamp[-1]-timeStamp[-2]; //in case the reset timer occurs in between
  currentState(0) = measure[0](0);//speed is copied
  currentState(1) = ( measure[0](0)-measure[-1](0) )/deltaT ;
  currentState(2) = measure[0](1); //copy mAmps
  state.push( currentState);
};

stateType RW::integrateStateEq(stateType s,controlInputType u0,timeType deltaT) const{
  //estimate of next state
  stateType nextState;
  nextState(0) = s(0) + s(1)*deltaT; //Simple integration
  nextState(1) = s(1); //assume constant torque
  nextState(2) = rpm2mAmp(nextState(0).value);; //assume this state... nextState(0);
  std::cout<<u0<<std::endl;
  return nextState;
};

measureType RW::observationModel(stateType x) const{
  //Given a state x, tell me what the observation would be.
  measureType probableRead;
  probableRead(0) = x(0); //RPM
  probableRead(1) = rpm2mAmp( x(0).value ); // estimate mAmp
  return probableRead;
};

controlInputType RW::controlLaw(stateType stateNow ,stateType target) const{
  //Target is a state vector, however we are interested only in the value of the derivative, target(1)
  float k = 0.14;
  //float kp = 1;
  //float error = kp*(stateNow(1)-target(1)).value;<- First step to make it close loop
  //float rpmTarget =((target(1)+error)/k+stateNow(0)).value;
  float rpmTarget = ( target(1)/k + stateNow(0) ).value;
  float pwmControl = rpm2Pwm(rpmTarget);
  return pwmControl;
};

bool RW::steadyState() const {
  if ((state[0](1).value == data(0,2) )&&(state[-1](1).value == data(0,2) )&&(state[-2](1).value ==  data(0,2) ))
    return true; //derivative compatible with zero for all timesteps
  else
    return false;
};

//=== RW specific =============================================================
float RW::rpm2Pwm( float rpmTarget)const{
  //"Static" mapping between pwm comand and equilibrium RPM
  float a = -9.8005;
  float b = 607.1753;
  float c1 = 650.7964;
  float commandGuess1 = (-b+sqrt(pow(b,2)-4.0*a*(c1-rpmTarget) ) )/2.0/a;
  //float commandGuess2 = (-b-sqrt(pow(b,2)-4.0*a*(c1-rpmTarget) ) )/2.0/a;
  //float commandMin = min(commandGuess1,commandGuess2);
  //return commandMin;
  return commandGuess1; //presumably is the smallest...
};

dataL RW::mAmp2Rpm(dataL mA) const{
  float a = 4.289*pow(10,-6);
  float b = -1.764*pow(10,-2);
  float c1 = 116.1;
  float rpmGuess1 = (-b+sqrt(pow(b,2)-4.0*a*(c1-mA.value) ) )/2.0/a;
  //float rpmGuess2 = (-b-sqrt(pow(b,2)-4.0*a*(c1-mA.value) ) )/2.0/a;
  //float rpm = max(rpmGuess1,rpmGuess2);
  return dataL(rpmGuess1,750); //+- is an estimate
};

dataL RW::rpm2mAmp(dataL rpm) const{
  float a = 4.289*pow(10,-6);
  float b = -1.764*pow(10,-2);
  float c = 116.1;
  dataL mA = a*pow(rpm,2)+b*rpm+c;
  return mA;
};
