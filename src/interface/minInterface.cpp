#include "../../include/minimalInterface/minInterface.h"
//#include <Arduino.h> //include types & constants of Wiring core API
#include <iostream>
using namespace std;

unsigned long int timeMicro(){
//  return micros(); for arduino
  cout<<"time micro invoked"<<endl;
  return 10;
}

void setDigitalPinAsInput(int pin){
  //pinMode(pin,INPUT);
  cout<<"Set Digital pin "<<pin <<" as input"<<endl;
}

void setDigitalPinAsOutput(int pin){
  //pinMode(pin,OUTPUT);
  cout<<"Set Digital pin "<<pin <<" as output"<<endl;
}

int readAnalogPin(int pin){
  //return analogRead(pin);
  cout<<"Read Analog pin "<<pin <<" returns 500"<<endl;
  return 500;
}

bool readDigitalPin(int pin){
  //return digitalRead(pin);
  cout<<"Read Digital pin "<<pin <<" returns true"<<endl;
  return true;
}

void writeDigitalPin(int pin, bool value){
  //digitalWrite(pin, value);
  cout<<"Set Digital pin "<<pin <<" to "<< value <<endl;
}

void writeAnalogPin(int pin, int value){
  //analogWrite(pin, value)
  cout<<"Set Analog pin "<<pin <<" to "<< value<<endl;
}
