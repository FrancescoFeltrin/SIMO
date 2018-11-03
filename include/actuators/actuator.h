// generic hierarchy 1/10/2018
#ifndef ACTUATOR_H
#define ACTUATOR_H

//Set up the ESC and command it
// include types & constants of Wiring core API
//#include <Arduino.h>

class Actuator{
public:
  virtual float inputMin() const = 0;
  virtual float inputMax() const = 0;
  virtual void command(float) = 0; //pass the comand to the actual actuator

  virtual void safeHold();
  virtual void safeStop();
  virtual void initialize();

  virtual void printSerialUnit() const = 0;

};

#endif
