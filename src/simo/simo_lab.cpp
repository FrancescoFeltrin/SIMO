#include "../../include/simo/simo.h"
#include "../../include/units/units.h"
#include "../../include/sensors/sensor.h"
#include "../../include/minimalInterface/minInterface.h"

Simo_lab::Simo_lab(Actuator & output, Sensor & mainSensor): Simo(output, mainSensor){}

void Simo_lab::printCSVheader() const{
  vector<Sensor*> sensorsV = attachedSensors();
  int n = sensorsV.size();
  string tab = " \t ";
  string nl  = " \n ";
  string val = "val";
  string error  = "err";
  for (int i=0; i < n ; ++i){
    print2terminal(sensorsV[i]->id());
    print2terminal(tab);
    print2terminal(sensorsV[i]->unit());
    print2terminal(tab);
  }
  print2terminal(nl);
  for (int i=0; i < n ; ++i){
    print2terminal(val);
    print2terminal(tab);
    print2terminal(error);
    print2terminal(tab);
  }
  print2terminal(nl);
}

void Simo_lab::printAllMeasure()const{
  vector<data> measure = currentMeasure();
  int n = measure.size();
  string tab = " \t ";
  string nl  = " \n ";
  for (int i=0; i < n ; ++i){
    print2terminal(measure[i].value );
    print2terminal(tab);
    print2terminal(measure[i].error );
    print2terminal(tab);
  }
}
