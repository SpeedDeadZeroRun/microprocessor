#define LED 16
#define Button_Pin 18

hw_timer_t *My_timer = NULL;
int LED_Value = 0;
int C = 477, D = 426, E = 379, F = 358, G = 319, A = 284;
float a[5] = { 2, 1.5, 1, 0.67, 0.5 };
int melody[44] = {C,C,G,G,A,A,G,F,F,E,E,D,D,C,G,G,F,F,E,E,D,G,G,F,F,E,E,D,C,C,G,G,A,A,G,F,F,E,E,D,E,D,E,C};
int tempo[44] = {500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,400,100,400,100,1000};
int count1 = 2;
int runner = 0;
// This is the Timer ISR. It is automatically called
// on a timer alarm event.
void IRAM_ATTR onTimer() {
  digitalWrite(LED, !digitalRead(LED));
}
void IRAM_ATTR Trigger() {
  count1 = (++count1) % 5;
}

void setup() {
  Serial.begin(9600);
  pinMode(Button_Pin, INPUT);
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);              // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true);  // point to the ISR
  attachInterrupt(Button_Pin, Trigger, FALLING);
}
void loop() {
  timerAlarmWrite(My_timer, melody[runner], true);
  timerAlarmEnable(My_timer);
  delay(tempo[runner] * a[count1]);
  timerAlarmDisable(My_timer);
  delay(50 * a[count1]);
  runner = (++runner) % 44;
 
}