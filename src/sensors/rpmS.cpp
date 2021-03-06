#include "../../include/units/units.h"
#include "../../include/sensors/rpmS.h"
#include "../../include/minimalInterface/minInterface.h"

RpmS::RpmS(int pin_n,string id):HallS(pin_n,id){}

#ifdef ARDUINO_ARCH
data RpmS::readRaw() const{
  //NB: - The output is in microseconds/4 because the resolution of the function
  // "micros()" is 4 microseconds. Minimum RPM = 457 RPM
  //    - Maximum time used by the measurement 2*max_time = 256 ms.

  //interval between two edges in ms
  bool current_value; //the digital value of the incoming analog signals
  bool prev_value = 1;

  unsigned long t_first, t_second; //time variables
  unsigned long reading_time,t_start;

  unsigned long DeltaT_mus = 0; //4,294,967,295 -> 4294 s
  unsigned long max_time; // [micro seconds] maximum time for the measurement


  max_time = 32766*4; // max value that fits in the output (int)
                      // NB: if you change this you increase the minimum RPM that you can detect.
  t_start = timeMicro();
  reading_time = 0;
  t_first = 0;
  while(reading_time < max_time){
     reading_time  = timeMicro()-t_start;
     current_value = (HallS::readRaw()).value; //should be either 1 or 0
     if (prev_value == 0 && current_value == 1 && t_first > 0) { //Second rising edge
        t_second = timeMicro();
        DeltaT_mus = t_second - t_first;
        reading_time = max_time+1;
    }
    if (prev_value == 0 && current_value == 1 && t_first == 0){
        t_first = timeMicro(); // First rising edge
        reading_time = 0; //from now, abort if you don't see anything before max_time.
    }
    prev_value = current_value;
  }
  DeltaT_mus = DeltaT_mus / 4; //compress to fit unsigned int
  data dT_mus(DeltaT_mus,2);    //up to 32 000 ->x4 ->approx 0.128 seconds
                                   //max error is given by the combined uncertanty of the two rising edges
                                   //err = sqrt(4^2+4^2)/4->1.41;
  return dT_mus;
}

#endif /*ARDUINO_ARCH */
#ifdef CPU_ARCH
data RpmS::readRaw() const{
  //NB: proto stuff
  return 10;
}
#endif /*CPU_ARCH*/

dataL RpmS::interpret(const dataL & deltaT) const{
  dataL RPM;
  dataL deltaT_mus = deltaT*4; // Conversion to microseconds... this might overflow the int...
  if (deltaT > 0){
      RPM = 60000000.0 / deltaT_mus ; //this is larger than an int!
    }
  else
      RPM = dataL(0,460/3); //I am sure that it is between [-460,+460]-> 3 sigma
  return  RPM;
}

int RpmS::minValue() const{
  return 0;
}
int RpmS::maxValue() const{
  return 20000;
}
string RpmS::unit() const{
  return "rpm"; //rpm
}
