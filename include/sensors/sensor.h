//Set up the ESC and command it
#ifndef SENSOR_H
#define SENSOR_H

#include "../units/units.h"
#include "../minimalInterface/minInterface.h"

/* A minimal interface for a sensor class:
  - "data" is a class that stores both a value and the error. It automatically perform
    basic error propagation (it adds errors in the "right way")
  - "readRaw" provides the fastest, minimal overhead to read the hardware. It does
    no interpretation of the data.
  - "interpret" produces a data that is in the unit identified by "unit()"
  - "read" is a simple readRaw + average + interpret.
*/

class Sensor{
public:
  Sensor();
  virtual data readRaw() const = 0; // quickest possible way to get data, no processing
  virtual dataL interpret(const dataL &) const = 0; // converts the ADC digital value in the measurement
  virtual dataL read(unsigned int = 3) const;      // reads n times and then interprets the average

  virtual int minValue() const = 0;   // Minium interpreted value
  virtual int maxValue() const = 0;
  virtual string id() const = 0;    // Individual sensor name
  virtual string unit() const = 0;  // unit of the interpreted value
};

class DigitalS: public Sensor{
private:
  byte pin;
  string name;
public:
  DigitalS(int,string);
  virtual data readRaw() const;
  virtual int minValue() const;
  virtual int maxValue() const;
  virtual string id() const;
  virtual string unit() const =0;
};

class AnalogS: public Sensor{
private:
  byte pin;
  string name;
public:
  AnalogS(int,string);
  virtual data readRaw() const;
  virtual int minValue() const;
  virtual int maxValue() const;
  virtual string id() const;
  virtual string unit() const =0;
};

#endif
