#include "../../include/sensors/sensor.h"
#include "../../include/units/units.h"
//#include "../../include/statistic/statistic.h"
#include "../../include/statistic/sAnalysis.h"

Sensor::Sensor(){}

dataL Sensor::read(unsigned int n) const{
  data raw[n]; //array
  for (unsigned int i = 0; i < n; i++)
    raw[i] = readRaw();
  dataL worstcase = sAnalysis(raw,n);
  return interpret(worstcase);
}


dataL Sensor::interpret(const dataL & input) const{
  return input;
}
