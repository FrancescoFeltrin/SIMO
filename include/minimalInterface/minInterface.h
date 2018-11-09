#ifndef MININTERFACE_H
#define MININTERFACE_H
#include<iostream>
//#include <Arduino.h>

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
using byte = unsigned char; // comment this for arduino.
using string = std::string;      //arduino does not implement string as strandard c++

unsigned long int timeMicro();
void setDigitalPinAsInput(int pin);
void setDigitalPinAsOutput(int pin);

bool readDigitalPin(int pin);
int readAnalogPin(int pin);

void writeDigitalPin(bool value);
void writeAnalogPin(int value);

// Interface
void print2terminal(const string &); // if available
void print2terminal(const int &); // if available
void print2log(const string&); //
void print2log(const int&); //
bool inputFromTerminal(const string & promt);
#endif
