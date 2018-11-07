#include "../../include/sensors/sensor.h"
#include "../../include/units/units.h"
#include "../../include/minimalInterface/minInterface.h"

AnalogS::AnalogS(int pin_n,string id): pin(pin_n),name(id){ }

data AnalogS::readRaw() const{
  unsigned int errADC = 2;
  data output(readAnalogPin(pin), errADC);
  return output;
}

int AnalogS::minValue() const{ // The arduino has a 10 bits ADC
  return 0;
}

int AnalogS::maxValue() const{ // The arduino has a 10 bits ADC
  return 1023;
}

string AnalogS::id() const{
  return name;
}

string AnalogS::unit() const{
  return "bit";
}
