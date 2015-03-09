#define LED_PIN 2
#define BUT_PIN_ACELERA 7
#define BUT_PIN_DESACELERA 4
unsigned long old,now,spd, now_acelera, now_desacelera;
int but_acelera, but_desacelera;

int state = HIGH;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN_ACELERA, INPUT);
  pinMode(BUT_PIN_DESACELERA, INPUT);
  old = millis();
  now_acelera = millis()+1000;
  now_desacelera = millis();
  but_acelera = 0;
  spd = 100;
}

void loop() {
  now = millis();
  if(now >= old + spd)
  {
    digitalWrite(LED_PIN, state);   
    old = now;
    state = !state;
  }
  if(digitalRead(BUT_PIN_ACELERA) > but_acelera)
  {
    now_acelera = millis();
    spd -= 25;
  }
  but_acelera = digitalRead(BUT_PIN_ACELERA);
  if(digitalRead(BUT_PIN_DESACELERA) > but_desacelera){
   now_desacelera = millis();
   spd += 25; 
  }
  but_desacelera = digitalRead(BUT_PIN_DESACELERA);
  if(abs(now_desacelera - now_acelera) <= 500)
  {
    digitalWrite(LED_PIN, LOW);
    while(1);
  }
}
