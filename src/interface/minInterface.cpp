#include "../../include/minimalInterface/minInterface.h"
/*Depending on where you are deploying, it chooses the hopefully correct implementation
  It is nothing but a bunch of wrapper
*/

#ifdef ARDUINO_ARCH
unsigned long int timeMicro(){
  return micros();// for arduino
}

void setDigitalPinAsInput(int pin){
  pinMode(pin,INPUT);
}

void setDigitalPinAsOutput(int pin){
  pinMode(pin,OUTPUT);
}

int readAnalogPin(int pin){
  return analogRead(pin);
}

bool readDigitalPin(int pin){
  return digitalRead(pin);
}

void writeDigitalPin(int pin, bool value){
  digitalWrite(pin, value);
}

void writeAnalogPin(int pin, int value){
  analogWrite(pin, value);
}

// Interface
void print2terminal(const string & msg){
   Serial.print(msg);
}

void print2terminal(const int & value){
  Serial.print(value);
}

void print2log(const string& msg){
     Serial.print("LOG:");
     Serial.print(msg);
}

void print2log(const int& value){
  Serial.print("LOG:");
  Serial.print(value);
}

bool inputFromTerminal(const string & promt){
  print2terminal(promt);
  string options = "(Y/N) \n";
  print2terminal(options);
  char Answ;
  if(Serial.available() > 0){
    Answ = Serial.read();
    Serial.print(" I received: ");
    Serial.println(Answ);
  }
  if (Answ == 'Y') return true;
  if (Answ == 'N') return false;
  else print2terminal(" Input not recognized");
  return false;
}
#endif /* ARDUINO_ARCH */
/////// CPU
#ifdef CPU_ARCH
#include <iostream>
using namespace std;

unsigned long int timeMicro(){
  cout<<"time micro invoked"<<endl;
  return 10;
}

void setDigitalPinAsInput(int pin){
  cout<<"Set Digital pin "<<pin <<" as input"<<endl;
}

void setDigitalPinAsOutput(int pin){
  cout<<"Set Digital pin "<<pin <<" as output"<<endl;
}

int readAnalogPin(int pin){
  cout<<"Read Analog pin "<<pin <<" returns 500"<<endl;
  return 500;
}

bool readDigitalPin(int pin){
  cout<<"Read Digital pin "<<pin <<" returns true"<<endl;
  return true;
}

void writeDigitalPin(int pin, bool value){
  cout<<"Set Digital pin "<<pin <<" to "<< value <<endl;
}

void writeAnalogPin(int pin, int value){
  cout<<"Set Analog pin "<<pin <<" to "<< value<<endl;
}


// Interface
void print2terminal(const string & msg){
  cout<<msg;
}

void print2terminal(const int & value){
  cout<<value;
}

void print2log(const string& msg){
  cout<<"Log: "<< msg<<endl;
}

void print2log(const int& value){
  cout<<"Log: "<< value << endl;
}

bool inputFromTerminal(const string & promt){
  print2terminal(promt);
  string options = "(Y/N) \n";
  print2terminal(options);
  char Answ;

  cin >> Answ;
  if (Answ == 'Y') return true;
  if (Answ == 'N') return false;
  else print2terminal(" Input not recognized");
  return false;
}
#endif /* CPU_ARCH */
