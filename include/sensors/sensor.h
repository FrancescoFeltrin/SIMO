//Set up the ESC and command it
#ifndef SENSOR_H
#define SENSOR_H

// include types & constants of Wiring core API
//#include <Arduino.h>

class Sensor{
private:
  int pin;
  unsigned long maxTimeMicro; //maximum time for a single reading
public:
  Sensor(int);
  Sensor(int, unsigned long);
  int rev_pin() const; //reveal pin, useful for derived classes
  //float readStat(int) const; //read n times and return average
  void setMaxT(unsigned long);
  unsigned int revealMaxT() const;
  virtual unsigned int readRaw() const=0; //digital read, without interpretation (by default the analogue one)
  virtual float interpret(unsigned int) const=0; //process a data given
  virtual float interpret(float) const;
  virtual float interpret() const;// read curret data and interpret
  virtual float quickRead(int = 5) const; // Multiple read, return interpreted average
  virtual float interpretDeltaAt(float,float) const; //if sensitivity is not linear, this is important
  //virtual float interpretDerivative() const;
  virtual void print2serial() const;
  virtual void serialPrintSensorName() const=0; // Show class Identifier
  virtual void serialPrintUnit() const=0; // ->interpreted signal units
};

/* The whole implementation is beside the point
class Current_S: public Sensor{
public:
  Current_S(int);
  virtual float interpret(unsigned int) const; //interpret in amps
  virtual float interpret(float) const;
  virtual void serialPrintSensorName() const; // Show class Identifier
  virtual void serialPrintUnit() const; // ->interpreted signal units
};

class Hall_S: public Sensor{
public:
  Hall_S(int);
  void setPort();
  virtual unsigned int readRaw()const; //magnet present or not
  virtual float interpret(unsigned int) const;
  virtual void serialPrintSensorName() const;
  virtual void serialPrintUnit() const;
};

class RPM_S: public Hall_S{
public:
  RPM_S(int);
  virtual unsigned int readRaw()const; //get interval in ms
  virtual float interpret(unsigned int)const; //make it rpm
  virtual float interpret(float)const; //make it rpm
  virtual void serialPrintSensorName()const;
  virtual void serialPrintUnit()const;
  virtual void print2serial()const;
};*/

#endif
