#include "../../include/sensors/currentS.h"
#include <cmath>
/* Implemented for the ACS712 -20 Amps sensor.
   Ideally, you would have a class for current sensor that just implements the
   return units (Amps or mAmps) and then you would derive specific sensors.
   For simplicity, I will not do it now.
*/

CurrentS::CurrentS(int pin_n,char id):AnalogS(pin_n,id){};

data CurrentS::interpret(const data & bitRead) const{
  int ACSoffset = 2500;
  int mApermV = 10;

  double mV;
  double mA;
  double convmVmA = 48.828125;// =5000 mV /1024 bits * 10mA/mV ;

  mV = ( ((double) bitRead.value) / 1024.0) * 5000; // Gets you mV
  mA = ((mV - ACSoffset) * mApermV);
  unsigned int quantizationError = round( ((double) bitRead.error )*convmVmA );

  data output(mA,quantizationError);
  return output;
}

int CurrentS::minValue() const{
  return -20000;
}

int CurrentS::maxValue() const{
  return +20000;
}

char CurrentS::unit() const{
  return 'A'; //Should be mA
};
