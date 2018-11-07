
#include "../../include/sensors/hallS.h"
#include "../../include/units/units.h"

HallS::HallS(int pin_n,string id):DigitalS(pin_n,id){}

data HallS::readRaw() const{
  return -(DigitalS::readRaw()-1); //inverts the reading;
  //This should give -> 1 there IS  A MAGNET
 //                  -> 0 there is NO MAGNET
}

string HallS::unit() const {
  return "bool";
}
