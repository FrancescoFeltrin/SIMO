#ifndef BRUSHLESS_H
#define BRUSHLESS_H

#include "simo.h"
#include "../units/units.h"
//#include "../sensors/sensor.h"
#include "../sensors/rpmS.h"
#include "../sensors/currentS.h"
#include "../actuators/esc.h"
#include "../minimalInterface/minInterface.h"

#include<vector>
using namespace std;
/* Set up to control a brushless engine
*/

class Brushless: public Simo_lab{
public:
  Brushless(Esc &, RpmS &,CurrentS &);
  virtual float computeControlInput(const vector<data> & targetState) const = 0;
  virtual vector<data> integrateStateEq(const vector<data>& state,const unsigned int & Dt_ms) const = 0;  //need to implement state equation
  virtual vector<data> observeState(const vector<data> & state) const  = 0; //returns expected measurements
  virtual vector<data> stateObserver() const = 0; //Do whatever you need to estimate the state from measuraments
  virtual void checkForFailureSigns(const vector<data> & expectedMeasure) = 0;
};

#endif
