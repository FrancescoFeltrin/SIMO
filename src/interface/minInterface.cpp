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


// Interface
void print2terminal(const string & msg){
  //   Serial.print(string);
  cout<<msg;
}

void print2terminal(const int & value){
  //   Serial.print(value);
  cout<<value;
}

void print2log(const string& msg){
  //   Serial.print("LOG:");
  //   Serial.print(string);
  cout<<"Log: "<< msg<<endl;
}

void print2log(const int& value){
  //   Serial.print("LOG:");
  //   Serial.print(value);
  cout<<"Log: "<< value << endl;
}

bool inputFromTerminal(const string & promt){
  print2terminal(promt);
  string options = "(Y/N) \n";
  print2terminal(options);
  char Answ;
 /*if(Serial.available() > 0){
   Ans = Serial.read();
   Serial.print(" I received: ");
   Serial.println(Ans);
 }*/
  cin >> Answ;
  if (Answ == 'Y') return true;
  if (Answ == 'N') return false;
  else print2terminal(" Input not recognized");
  return false;
}
