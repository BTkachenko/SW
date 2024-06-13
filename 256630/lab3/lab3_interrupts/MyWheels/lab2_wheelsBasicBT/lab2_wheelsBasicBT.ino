#include "Wheels.h"
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

Wheels w;
volatile char cmd;

void setup() {
  // put your setup code here, to run once:
  w.attach(IN1,IN2,ENA,IN4,IN3,ENB);
  pinMode(BEEPER, OUTPUT);
  Timer1.initialize();
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  w.forward();
  w.setSpeed(100);
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'f': w.goForward(10);break;
      case 'b': w.goBack(10);break;
      case 'w': w.forward(); break;
      case 'x': w.back(); BackBeeper(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': Clear(); w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
}

void Clear(){
    Timer1.detachInterrupt();
    digitalWrite(BEEPER, LOW);

  }
// aktualizuje Timer1 aktualną wartością intPeriod
void BackBeeper() {
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(doBeep, 500000);
}

void doBeep() {
  digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}
