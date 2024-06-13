#include "Wheels.h"

#include "PinChangeInterrupt.h"

#define INTINPUT0 A0
#define INTINPUT1 A1
#define IN1 4
#define IN2 5

//1,2,A -lewo

//3,4,B - prawo
#define IN3 8
#define IN4 7

#define ENA 11
#define ENB 6
#define SPEED 60
#define BEEPER 13

Wheels w;
volatile int cnt0, cnt1;

void setup() {
  w.attach(IN1,IN2,ENA,IN4,IN3,ENB);
  w.setSpeed(150);

  w.forward();

  Serial.begin(9600);

  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  cnt0=0;
  cnt1=0;

  PCICR  = 0x02;  // włącz pin change interrupt dla 1 grupy (A0..A5)
  PCMSK1 = 0x03;  // włącz przerwanie dla A0, A1

}

void loop() {
  w.turnLeft(1);

  delay(250);
}

ISR(PCINT1_vect){
 if( (PINC & (1 << PC0)) ) 
 cnt0++;

 if( (PINC & (1 << PC1)) )
 cnt1++;
}
