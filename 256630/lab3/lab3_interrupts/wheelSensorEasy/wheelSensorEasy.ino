#include "Wheels.h"

#include "PinChangeInterrupt.h"

#define INTINPUT0 A0
#define INTINPUT1 A1
#define IN1 4
#define IN2 5

//1,2,A -lewo

//3,4,B - prawo
#define IN3 6
#define IN4 7

#define ENA 11
#define ENB 3
#define SPEED 60
#define BEEPER 13
Wheels w;
volatile int cnt0, cnt1;

void setup() {
  w.attach(IN1,IN2,ENA,IN4,IN3,ENB);
  w.setSpeed(100);

  Serial.begin(9600);

  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  cnt0=0;
  cnt1=0;

  w.goForward(1);

 attachPCINT(digitalPinToPCINT(INTINPUT0), increment, CHANGE);
 attachPCINT(digitalPinToPCINT(INTINPUT1), increment, CHANGE);
}

void loop() {
  Serial.print(w.cnt0);
  Serial.print(" ");
  Serial.println(w.cnt1);  
  delay(250);
}

void increment() {
 if( (PINC & (1 << PC0)) )
 {
 cnt0++;
 w.cnt0++;
 }
 if( (PINC & (1 << PC1)) ){
 cnt1++;
 w.cnt1++;
 }
}
