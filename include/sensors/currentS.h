#ifndef CURRENTS_H
#define CURRENTS_H

#include "sensor.h"
#include "../units/units.h"
#include "../minimalInterface/minInterface.h"

class CurrentS: public AnalogS{
public:
  CurrentS(int,string);
  virtual data interpret(const data &) const;

  virtual int minValue() const;
  virtual int maxValue() const;
  virtual string unit() const;
};

#endif
