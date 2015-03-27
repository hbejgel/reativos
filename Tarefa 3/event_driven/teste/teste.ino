#include "event_driven.h"
#define LED_PIN 13
#define BUT_PIN_ACELERA 11
#define BUT_PIN_DESACELERA 12

unsigned long spd;
int aceso;

void custom_init(){
  button_listen(BUT_PIN_DESACELERA);
  button_listen(BUT_PIN_ACELERA);
  pinMode(LED_PIN, OUTPUT);
  spd = 200;
  aceso = LOW;
}

void button_changed(int pin, int state){
  if(pin == BUT_PIN_ACELERA)
  {
    spd -= state * 25;
  } else {
    spd += state * 25;
  }
}

void timer_expired(){
  digitalWrite(LED_PIN, aceso);
  aceso = !aceso;
  timer_set(spd);
}
