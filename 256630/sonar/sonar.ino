#include "Wheels.h"

#include <PinChangeInterrupt.h>
#include <Servo.h>

// piny dla sonaru (HC-SR04)
#define TRIG A4
#define ECHO A5

// pin kontroli serwo (musi być PWM)
#define SERVO 3

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

Servo serwo;

volatile int angle;


void setup() {
  w.attach(IN1,IN2,ENA,IN4,IN3,ENB);
  w.setSpeed(150);

  angle = 90;
  pinMode(TRIG, OUTPUT);    // TRIG startuje sonar
  pinMode(ECHO, INPUT);     // ECHO odbiera powracający impuls

  Serial.begin(9600);

  serwo.attach(SERVO);
  w.forward();

/* rozejrzyj się w zakresie od 0 stopni (patrz na jedną burtę)
 *  do 180 stopni (patrz na prawą burtę). Wydrukuj na konsoli
 *  kierunek patrzenia i najbliżej widziany obiekt (pojedynczy pomiar)
 */

  
/* patrz przed siebie */
  serwo.write(angle);

}

void loop() { 
    unsigned int distance = lookAndTellDistance(angle);
    if(distance < 15 )
  {
    w.stop();
    int newdirangle = findway();
    serwo.write(newdirangle);
    Serial.println(newdirangle);
    delay(3000);
    }
    else {
      w.forward();
    }
  }



int findway(){
  unsigned int bestangle = 90;
 int bestdistance = 0;
   for(byte angle = 0; angle < 180; angle+= 5) {
    unsigned int t = lookAndTellDistance(angle);
    if( bestdistance < t){
      bestdistance = t;
      bestangle = angle;
      }
    delay(150);
  }
  return bestangle;
  }
unsigned int lookAndTellDistance(byte angle) {
  
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;

  serwo.write(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
  return distance = tot/58;

}
