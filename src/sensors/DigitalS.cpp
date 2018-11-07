#include "../../include/sensors/sensor.h"
#include "../../include/statistic/statistic.h"
#include "../../include/units/units.h"
#include "../../include/minimalInterface/minInterface.h"

DigitalS::DigitalS(int pin_n,string id): pin(pin_n),name(id){
    setDigitalPinAsInput(pin);
}

data DigitalS::readRaw() const{
  data output(readDigitalPin(pin),0);
  return output;
}

int DigitalS::minValue() const{ // The arduino has a 10 bits ADC
  return 0;
}

int DigitalS::maxValue() const{ // The arduino has a 10 bits ADC
  return 1;
}

string DigitalS::id() const{
  string copyName = name;
  return  copyName;
}

string DigitalS::unit() const{
  return "bit"; //should be bits
}
