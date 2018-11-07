// generic hierarchy 1/10/2018
#ifndef ACTUATOR_H
#define ACTUATOR_H

/* Actuator assumptions:
  - Monodimentional control input

*/

class Actuator{
public:
  Actuator();
  virtual void command(float) = 0;

  virtual float inputMin() const = 0;
  virtual float inputMax() const = 0;

  virtual void safeHold() = 0;
  virtual void safeStop() = 0;
  virtual void initialize() = 0;

  virtual char commandUnit() const = 0;
};

#endif
