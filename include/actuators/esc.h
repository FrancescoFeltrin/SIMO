#ifndef ESC_H
#define ESC_H

#include "actuator.h"
#include "../minimalInterface/minInterface.h"
//#include "Servo.h"

class Esc: public Actuator{
private:
  byte pin;
  //servo* srv_ptr;
  void setSpeed(float);
  static const int low_lv  = 1000;
  static const int high_lv = 2000;
  void low() const; //needed for initialization
  void high() const;
  void calibrate();
public:
  Esc(int pin_n);
  virtual void initialize();
  virtual float inputMin() const;
  virtual float inputMax() const;
  virtual void command(float); // comand in [%]

  virtual void safeHold();
  virtual void safeStop();
  virtual char commandUnit() const;
};

#endif
