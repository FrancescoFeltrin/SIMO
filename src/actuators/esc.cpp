#include "../../include/actuators/esc.h"
#include "../../include/minimalInterface/minInterface.h"

#ifdef ARDUINO_ARCH
  #include "Servo.h"
#endif

Esc::Esc(int pinN): pin(pinN){
  #ifdef ARDUINO_ARCH
    srv_ptr = new Servo; //the only one servo..
  #endif
};

void Esc::low() const{
  #ifdef ARDUINO_ARCH
    srv_ptr->writeMicroseconds(low_lv);
  #endif
};

void Esc::high() const{
  #ifdef ARDUINO_ARCH
    srv_ptr->writeMicroseconds(high_lv);
  #endif
};

void Esc::setSpeed(float Value){ //this is the only interface to the servo
  if (Value > inputMax())
      Value = inputMax();
  else if (Value < inputMin())
      Value = inputMin();
  int absValue = (Value/100.0)*(high_lv-low_lv)+low_lv;
  absValue = absValue;
  #ifdef ARDUINO_ARCH
    srv_ptr->writeMicroseconds(absValue);
  #endif
}

void Esc::command(float input){
  setSpeed(input);
}

void Esc::calibrate(){
  //set the max and min speed
  #ifdef ARDUINO_ARCH
  int value = 0;
  bool exit1 = false;
  bool exit2 = false;
  print2terminal("Setting top Speed (press 1 when you hear long beep-beep)");
  //Serial.println( "Setting top Speed (press 1 when you hear long beep-beep)");
  high();
  while (exit1 == false){
    if(Serial.available()>0){
      value = Serial.parseInt();
      if (value==1){
        exit1 = true;
        value = 0;
        print2terminal("Top speed set, Setting LOW Speed (press 1 after a lot of long beeps)");
        //Serial.println( "Top speed set, Setting LOW Speed (press 1 after a lot of long beeps)" );
        low();
        while (exit2 == false){
          if(Serial.available()>0){
            value = Serial.parseInt();
            if (value==1) exit2 = true;
          }
        }
        }
      }
    }
  print2terminal("Initialization is Done! ");
  #endif
}

void Esc::initialize(){
  #ifdef ARDUINO_ARCH
  int value = 0;
  int countTo1000 = 0;
  bool exit = false;
  srv_ptr->attach(pin);
  low();
  print2terminal("Initialize ESC(ONLY the first time)?  1 = YES / 2 = NO");
  //Serial.println("Initialize ESC(ONLY the first time)?  1 = YES / 2 = NO");
  while (exit == false){
    if(Serial.available()>0){
      value = Serial.parseInt();
      if (value==1){
        calibrate();
        exit = true;
      }
      if (value==2) exit = true;
   }
   delay(5);
   countTo1000++;
   if (countTo1000>1000) exit = true;
  }
  print2terminal("Initialization over.");
  //Serial.print("Initialization over.");
  low();
  #endif
}

float Esc::inputMin() const{
  return 5;
}

float Esc::inputMax() const{
  return 20;
}

void Esc::safeHold(){
}

void Esc::safeStop(){
  command(0);
}

char Esc::commandUnit() const{
  return '%';
}
