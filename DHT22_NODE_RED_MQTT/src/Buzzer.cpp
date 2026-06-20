#include <Arduino.h>
#include "Buzzer.h"

#define Buzzer 18
 

void BUZZER::buzzerpinsetup(){
  pinMode(Buzzer, OUTPUT);
}

void BUZZER::buzzer_on(int d){
  digitalWrite(Buzzer, 1);
  delay(d);
}

void BUZZER::buzzer_off(int d){
    
    delay(d);
}

void BUZZER::buzzer_beep(int d){
    
  delay(d);
}