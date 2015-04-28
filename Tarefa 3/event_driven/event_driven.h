/* Listeners */
void button_listen(int pin);
int timer_set(int ms);

/* Callbacks */
void button_changed(int pin, int state);
void timer_expired();

/* Init */
void custom_init();
