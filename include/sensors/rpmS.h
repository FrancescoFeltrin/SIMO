#ifndef RPMS_H
#define RPMS_H

#include "../units/units.h"
#include "hallS.h"
// This sensor measures the time interval between two consequtive "rising edge"
// given by the hall sensor measurment.

class RpmS : public HallS{
  RpmS(int,char);
  virtual data readRaw() const;
  virtual data interpret(const data &) const;
  virtual int minValue() const;
  virtual int maxValue() const;
  virtual char unit() const;
};

#endif
