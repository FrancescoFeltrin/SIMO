#ifndef HALLS_H
#define HALLS_H

#include "sensor.h"
#include "../units/units.h"
// Detects the presece or absence of a magnet.

class HallS : public DigitalS{
public:
  HallS(int,char);
  virtual data readRaw() const;
};

#endif
