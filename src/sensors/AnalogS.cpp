#include "../../include/sensors/sensor.h"
#include "../../include/statistic/statistic.h"
#include "../../include/units/units.h"

AnalogS::AnalogS(int pin_n,char id): pin(pin_n),name(id){}

data AnalogS::readRaw() const{
  return data(1023/2,2);        //Simple example
}

int AnalogS::minValue() const{ // The arduino has a 10 bits ADC
  return 0;
}

int AnalogS::maxValue() const{ // The arduino has a 10 bits ADC
  return 1023;
}

char AnalogS::id() const{
  return name;
}

char AnalogS::unit() const{
  return 'b';
}
