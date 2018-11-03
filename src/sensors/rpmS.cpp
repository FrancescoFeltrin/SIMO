
#include "../../include/units/units.h"
#include "../../include/sensors/rpmS.h"

RpmS::RpmS(int pin_n,char id):HallS(pin_n,id){}

data RpmS::readRaw() const{
  //NB: The output is in microseconds/4 because the resolution of the function
  // "micros()" is 4 microseconds. Minimum RPM = 45 ?

  //interval between two edges in ms
    /*bool current_value; //the digital value of the incoming analog signals
  bool prev_value = 1;

  unsigned long t_first, t_second; //time variables
  unsigned long reading_time,t_start;

  unsigned long DeltaT_mus = 0; //4,294,967,295 -> 4294 s
  unsigned long max_time; // [micro seconds] maximum time for the measurement


  max_time = max(32766*4);  //the max value that fits in the output (int)
  t_start = micros();
  reading_time = 0;
  t_first = 0;
  while(reading_time < max_time){
     reading_time  = micros()-t_start;
     current_value = (HallS::readRaw()).value; //should be either 1 or 0
     if (prev_value == 0 && current_value == 1 && t_first > 0) { //Second rising edge
        t_second = micros();
        DeltaT_mus = t_second - t_first;
        reading_time = max_time+1;
    }
    if (prev_value == 0 && current_value == 1 && t_first == 0)
        t_first = micros(); // First rising edge
    prev_value = current_value;
  }
  DeltaT_mus = DeltaT_mus / 4; //compress to fit unsigned int
  data DeltaT_ms(DeltaT_mus,2);    //up to 32 000 ->x4 ->approx 0.128 seconds
                                   //max error is given by the combined uncertanty of the two rising edges
                                   //err = sqrt(4^2+4^2)/4->1.41;
  */
  data DeltaT_ms(10000,2);
  return DeltaT_ms;
}

data RpmS::interpret(const data & deltaT) const{
  data RPM;
  data deltaT_mus = deltaT*4;
  if (deltaT > 0)
      RPM = 1000000.0 * 60.0 / deltaT_mus;
  else
      RPM = data(0,460/3);
  return  RPM;
}

int RpmS::minValue() const{
  return 0;
}
int RpmS::maxValue() const{
  return 20000;
}
char RpmS::unit() const{
  return 'r'; //rpm
}
