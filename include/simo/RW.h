#ifndef RW_H
#define RW_H
/* Navie attempt at the RW. It's target is a torque. DOES NOT follow standard
control theory.
*/
#include "simoN.h"
#include "labMode.h"

using stateType = Gmatrix<3,1,dataL>; //State vector size = 3 [angular speed, angular acc, current (mAmp)]
using measureType = Gmatrix<2,1,dataL>; //numeber of sensors = 2, [Rpm sensor, Amp sensor]
using controlInputType = float;
using timeType = long int;

class RW: public LabMode<2,3,3,3>{//SimoN<2,3,3,3>{
public:
  RW();
  RW(Actuator& a, Sensor* vec [2]);// Sensors need to be RPM and Current
  RW(const RW &) = default;
  RW& operator=(const RW&) = default;
  //  control functions (HIGH LEVEL).
  // getNewMeasure(); inherited
  virtual void estimateState();
  // computeControlInput(); inherited
  // applyControlInput(); inherited

  //  Lower level functions
  virtual        stateType integrateStateEq(stateType s0,controlInputType u0,timeType deltaT) const;
  virtual      measureType observationModel(stateType s) const;
  virtual controlInputType controlLaw(stateType state ,stateType target) const;

  virtual bool steadyState() const;
  //Specific function for the RW
  float  rpm2Pwm(float rpmTarget) const;
  dataL mAmp2Rpm(dataL mA) const;
  dataL rpm2mAmp(dataL rpm) const;
};

#endif /* RW_H */
