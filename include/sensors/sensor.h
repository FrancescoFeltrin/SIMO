//Set up the ESC and command it
#ifndef SENSOR_H
#define SENSOR_H

#include "../units/units.h"
// include types & constants of Wiring core API
//#include <Arduino.h>
/* A minimal interface for a sensor class:
  - "data" is a class that stores both a value and the error. It automatically perfor
    basic error propagation (it adds errors in the "right way")
  - "readRaw" provides the fastest, minimal overhead to read the hardware. It does
    no interpretation of the data. In this way, you can sample multiple sensor in
    rapid succession and pretend you have simultaneous readings.
  - "interpret" produces a data that is in the unit identified by "unit()"
  - "Data" is a simple readRaw+ average+ interpret.
*/


class Sensor{
public:
  Sensor();
  virtual data readRaw() const = 0; // quickest possible way to get data, no processing
  virtual data interpret(const data &) const = 0; //applies the interpretation function
  virtual data read(unsigned int = 3) const;      // reads n times and then interprets the average

  virtual int minValue() const = 0;   // Minium interpreted value
  virtual int maxValue() const = 0;
  virtual char id() const = 0;    // Individual sensor name
  virtual char unit() const = 0;  // unit of the interpreted value
};


class DigitalS: public Sensor{
private:
  int pin;
  char name;
public:
  DigitalS(int,char);
  virtual data readRaw() const;
  virtual int minValue() const;
  virtual int maxValue() const;
  virtual char id() const;
  virtual char unit() const;
};

class AnalogS: public Sensor{
private:
  int pin;
  char name;
public:
  AnalogS(int,char);
  virtual data readRaw() const;
  virtual int minValue() const;
  virtual int maxValue() const;
  virtual char id() const;
  virtual char unit() const;
};



/*
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
