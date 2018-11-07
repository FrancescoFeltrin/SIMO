#ifndef HALLS_H
#define HALLS_H

#include "sensor.h"
#include "../units/units.h"
#include "../minimalInterface/minInterface.h"
// Detects the presece or absence of a magnet.

class HallS : public DigitalS{
public:
  HallS(int,string);
  virtual data readRaw() const;
  virtual string unit() const;
};

#endif
