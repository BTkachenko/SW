#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2
#include "TimerOne.h"
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

// 0x18 - forward 0x52 -back 0x5A - right 0x8 - left 
// 0x1C OK = 28
// 0x45 -1 0x46 -2

void setup()
{
  Serial.begin(9600);
  Serial.println("PRESS ok to start");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  while(IrReceiver.decodedIRData.command != 28) {IrReceiver.decode();}
  Serial.println("Start");
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.command); 

      IrReceiver.resume(); // Enable receiving of the next value
  }
}
