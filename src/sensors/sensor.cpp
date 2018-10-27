//#include <Arduino.h>
//#include <ArduinoSTL.h>

#include <vector>
#include "../../include/sensors/sensor.h"
#include "../../include/statistic/statistic.h"
#include <iostream>

using namespace std;

Sensor::Sensor(int pin): pin(pin),maxTimeMicro(500000){}
Sensor::Sensor(int pin,unsigned long maxT): pin(pin),maxTimeMicro(maxT){}

/*unsigned int Sensor::readRaw() const{
  return (unsigned int) analogRead(pin);
}*/

/*float Sensor::readStat(int n) const{
  unsigned long int tot=0;
  int i;
  for(i=0;i<n; ++i)
    tot=tot+readRaw();
  return (float) tot/n;
}*/

void Sensor::setMaxT(unsigned long newMaxT){
  maxTimeMicro = newMaxT;
}

unsigned int Sensor::revealMaxT() const{
  return maxTimeMicro;
}

float Sensor::interpret(unsigned int value) const{
  return (float) value;
}

float Sensor::interpret(float value) const{
  return interpret((unsigned int) value);
}

float Sensor::interpret() const{
  unsigned int value;
  value = readRaw();
  return interpret( value );
}

float Sensor::quickRead(int N) const{
  vector<int> res(N);
  for (int i=0; i<=N ; i++)
    res[i] = readRaw();
  float avgRaw = mean( &res );
  /*Serial.print(" avg: ");
  Serial.print(avgRaw);
  Serial.print(" ");*/
  return interpret(avgRaw);
}

float Sensor::interpretDeltaAt(float Delta, float offset)const{
  float newValue,interpretedDelta;
  newValue = offset + Delta;
  interpretedDelta = abs(interpret(newValue) - interpret(offset));
  return interpretedDelta;
}

/*float Sensor::interpretDerivative()const{
  unsigned long t0,t1,t2;
  float v0,v1,v2;
  float d1,d2,dAvg;
  t0 = micros();
  v0 = interpret();
  t1 = micros();
  v1 = interpret();
  t2 = micros();
  v2 = interpret();
  if (t0 != t1)
    d1 = (v1-v0)*1.0 / (t1-t0);
  else
    d1 =(v1-v0)*1.0 / 4; //measure / microsecodns
  if (t2 != t1)
    d2 = (v2-v1)*1.0 / (t2-t1);
  else
    d2 =(v2-v1)*1.0 / 4; //measure / microsecodns
  dAvg = (d1 +d2)*1.0/2;
  return dAvg*1000000; //measure* seconds
}*/

void Sensor::print2serial()const{
  serialPrintSensorName();
  //Serial.print(interpret(),3); //with 3 decimal places
  cout<<interpret();
  serialPrintUnit();
};

int Sensor::rev_pin()const{
  return pin;
}
