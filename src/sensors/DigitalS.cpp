#include "../../include/sensors/sensor.h"
#include "../../include/statistic/statistic.h"
#include "../../include/units/units.h"

DigitalS::DigitalS(int pin_n,char id): pin(pin_n),name(id){
    //pinMode(pin,INPUT);
}

data DigitalS::readRaw() const{
  return data(1,0); //Simple example
}

int DigitalS::minValue() const{ // The arduino has a 10 bits ADC
  return 0;
}

int DigitalS::maxValue() const{ // The arduino has a 10 bits ADC
  return 1;
}

char DigitalS::id() const{
  return name;
};

char DigitalS::unit() const{
  return 'b'; //should be bits
};
