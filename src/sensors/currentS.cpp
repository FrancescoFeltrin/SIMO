#include "../../include/sensors/currentS.h"
#ifdef CPU_ARCH
  #include <cmath>
#endif
#ifdef ARDUINO_ARCH
  #include <math.h>
#endif
/* Implemented for the ACS712 -20 Amps sensor.
   Ideally, you would have a class for current sensor that just implements the
   return units (Amps or mAmps) and then you would derive specific sensors.
   For simplicity, I will not do it now.
*/

CurrentS::CurrentS(int pin_n,string id):AnalogS(pin_n,id){}

data CurrentS::interpret(const data & bitRead) const{
  int ACSoffset = 2500;
  int mApermV = 10;

  double mV;
  double mA;
  double convmVmA = 48.828125;// =5000 mV /1024 bits * 10mA/mV ;

  mV = ( ((double) bitRead.value) / 1024.0) * 5000; // Gets you mV
  mA = ((mV - ACSoffset) * mApermV);
  unsigned int quantizationError = round( ((double) bitRead.error )*convmVmA );

  data output(round(mA),quantizationError);
  return output;
}

int CurrentS::minValue() const{
  return -20000;
}

int CurrentS::maxValue() const{
  return +20000;
}

string CurrentS::unit() const{
  return "mA"; //Should be mA
}
