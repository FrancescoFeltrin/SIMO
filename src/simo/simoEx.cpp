#include "../../include/simo/simoEx.h"
/* An example of a system in which you directly observe the state, and apply
a PID control */

/*NB: from the simoEx.h file
using stateType = Gmatrix<2,1,dataL>; //State vector size = 2
using measureType = Gmatrix<2,1,dataL>; //numeber of sensors = 2
using controlInputType = float;
*/

//SimoEx::SimoEx(){};
SimoEx::SimoEx(Actuator& a, Sensor* vec [2]):SimoN(a,vec){};

void SimoEx::estimateState(){
  Gmatrix<2,2,dataL> C;
  C(0,0) = 1.0; C(0,1) = 0.0;
  C(1,0) = 0.0; C(1,1) = 1.0;
  state.push( C*measure[0]);
}

stateType SimoEx::integrateStateEq(stateType s0,controlInputType u0,timeType deltaT) const{
  Gmatrix<2,2,dataL> A;
  A(0,0) = 1.0; A(0,1) = 0.0;
  A(1,0) = 1.0; A(1,1) = 1.0;
  Gmatrix<2,1,dataL> B;
  B(0) = 0.0;
  B(1) = 1.0;
  cout<<"State "<< s0(1) <<" control "<<u0<<" Delta Time "<< deltaT<< std::endl;
  return (A*s0+B*u0)*deltaT;
}

measureType SimoEx::observationModel(stateType s) const{
  Gmatrix<2,2,dataL> H;
  H(0,0) = 1.0; H(0,1) = 0.0;
  H(1,0) = 0.0; H(1,1) = 1.0;
  measureType probableRead;
  probableRead = H*s;
  return probableRead;
}

controlInputType SimoEx::controlLaw(stateType stateNow ,stateType target) const{
  Gmatrix<1,1,dataL> U;
  U = (target-stateNow).t() * (target-stateNow);
  float u = U(1).value;
  cout<<"State "<< stateNow(0) <<" control "<< target(0)<<endl;
  return u;
}
