#ifndef CURRENTS_H
#define CURRENTS_H

#include "sensor.h"
#include "../units/units.h"

class CurrentS: public AnalogS{
public:
  CurrentS(int,char);
  virtual data interpret(const data &) const;

  virtual int minValue() const;
  virtual int maxValue() const;
  virtual char unit() const;
};

#endif
