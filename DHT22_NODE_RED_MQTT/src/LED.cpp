#include <Arduino.h>
#include "LED.h"

#define LED1 _____ 
#define LED2 _____ 

void LED::ledpinsetup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void LED::led_on(int d){
  digitalWrite(LED1, 1);
  digitalWrite(LED2, 1);
  delay(d);
}

void LED::led_off(int d){
    
  delay(d);
}
   
void LED::led_blink(int d){
    
  delay(d);
}


