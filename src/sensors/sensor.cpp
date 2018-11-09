#include <vector> //#include <ArduinoSTL.h>
#include "../../include/sensors/sensor.h"
#include "../../include/statistic/statistic.h"
#include "../../include/units/units.h"

//#include <iostream>
//using namespace std;

Sensor::Sensor(){}

data Sensor::read(unsigned int n) const{
  vector<data> raw(n,0);
  for (unsigned int i = 0; i < n; i++)
    raw[i]= readRaw();
  data avg = mean(raw);
  data std = standardDev(raw,avg);
  data worstcase(avg.value, std.value + avg.error); // Is this correct?
  return interpret(worstcase);
}


data Sensor::interpret(const data & input) const{
  return input;
}
