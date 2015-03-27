#include "Arduino.h"
#include "event_driven.h"

#define MAX_PINS 2

int MyPins[MAX_PINS];
int PinStates[MAX_PINS];
int TotalPins = 0;
int Timer1, Timer2;

void button_listen(int pin){
   if(TotalPins >= MAX_PINS){
     return; 
   }
   MyPins[TotalPins++] = pin;
   pinMode(pin, INPUT);
}

int timer_set(int ms){
   if(Timer1 == -1){
     Timer1 = millis() + ms;
     return 1;
   } 
   else if(Timer2 == -1){
     Timer2 = millis() + ms; 
     return 1;
   }
   return -1;
}

void setup_timers(){
  Timer1 = -1;
  Timer2 = -1;
}

void start_arrays(){
  for(int i=0; i< MAX_PINS; i++)
  {
    PinStates[i] = 0;
    MyPins[i] = 0;
  }  
}

void setup() {
  start_arrays();
  setup_timers();
  custom_init();
}

void loop() {
    int button_state;
    for(int i=0; i<TotalPins; i++)
    {
       button_state = digitalRead(MyPins[i]);
       if(PinStates[i] != button_state){
         PinStates[i] = button_state;
         button_changed(MyPins[i], button_state);
       } 
    }
    if(Timer1 != -1 && millis() > Timer1)
    {
      Timer1 = -1;  
      timer_expired();
    }
    if(Timer2 != -1 && millis() > Timer2)
    {
      Timer2 = -1; 
      timer_expired();
    }
}
