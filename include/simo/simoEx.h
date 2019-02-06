#ifndef SIMOEX_H
#define SIMOEX_H

#include "simoN.h"

using stateType = Gmatrix<2,1,dataL>; //State vector size = 2
using measureType = Gmatrix<2,1,dataL>; //numeber of sensors = 2
using controlInputType = float;

class SimoEx: public SimoN<2,2>{
public:
  //SimoEx();
  SimoEx(Actuator& a, Sensor* vec [2]);
  //  control functions (HIGH LEVEL).
  // getNewMeasure(); inherited
  virtual void estimateState();
  // computeControlInput(); inherited
  // applyControlInput(); inherited

  //  Lower level functions
  virtual stateType integrateStateEq(stateType s0,controlInputType u0,timeType deltaT) const;
  virtual measureType observationModel(stateType s) const;
  virtual controlInputType controlLaw(stateType state ,stateType target) const;
};

#endif /* SIMOEX_H */
