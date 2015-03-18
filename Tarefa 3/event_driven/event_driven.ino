// User

void nosso_init(){
  timer_set(5000);
  timer_set(10000);
  button_listen(12);
  button_listen(11);
  pinMode(13, OUTPUT);
}

void button_changed(int pin, int state){
  if(pin == 11)
  {
    Serial.println("BUTTON 11");
    digitalWrite(13, HIGH);
  } else {
    Serial.println("BUTTON 10"); 
    digitalWrite(13, LOW);
  }
}

void timer_expired(){
  timer_set(1000);
  Serial.println("PRINTOU TEMPO");
}


// API

#define MAX_PINS 100

int MyPins[MAX_PINS];
int PinStates[MAX_PINS];
int TotalPins = 0;
int Timer1, Timer2;

void button_listen(int pin){
   MyPins[TotalPins++] = pin;
   pinMode(pin, INPUT);
}

void timer_set(int ms){
   if(Timer1 == -1){
     Timer1 = millis() + ms;
   } 
   else if(Timer2 == -1){
     Timer2 = millis() + ms; 
   }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  start_arrays();
  setup_timers();
  nosso_init();
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







