#ifndef MININTERFACE_H
#define MININTERFACE_H

#define CPU_ARCH  //Choose the architecture you would like. ONLY HERE
//#define ARDUINO_ARCH

// This is an attempt at portability;
// Ideally you would just update this file to deploy on a different hardware.
/*Minimal list of thigs I need
  -How to tell time -in us,ms,s etc
  -Set digital pin as input/output
  -Read/write digital pin
  -Read/write analog pin

  -Ouputs to some screen
  -Inputs from screen
  -Warning output
*/

#ifdef CPU_ARCH
  #include<iostream>
  using byte = unsigned char; // comment this for arduino.
  using string = std::string;      //arduino does not implement string as strandard c++
#endif

#ifdef ARDUINO_ARCH
  #include <Arduino.h>
  using string = String;
#endif

unsigned long int timeMicro();
void setDigitalPinAsInput(int pin);
void setDigitalPinAsOutput(int pin);

bool readDigitalPin(int pin);
int readAnalogPin(int pin);

void writeDigitalPin(bool value);
void writeAnalogPin(int value);

// Interface
void print2log(const string&); //<< should also be templates...
void print2log(const int&); //
bool inputFromTerminal(const string & promt);

// print 2 terminal in template
template<class T>
void print2terminal(const T& msg){
  #ifdef ARDUINO_ARCH
    Serial.print(msg);
  #endif
  #ifdef CPU_ARCH
    std::cout << msg;
  #endif
}

void wait(int); //to be used as little as possible!

#endif
