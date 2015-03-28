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
  timer_set(spd);
  aceso = LOW;
}

void button_changed(int pin, int state){
  Serial.println(spd);
  if(pin == BUT_PIN_ACELERA && state == HIGH)
  {
    spd *= 2;
  } else if(pin == BUT_PIN_DESACELERA && state == HIGH){
    spd /= 2;
  }
}

void timer_expired(){
  digitalWrite(LED_PIN, aceso);
  aceso = !aceso;
  timer_set(spd);
}
