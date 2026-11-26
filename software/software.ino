#include <Servo.h>

const int HOUR_SERVO_PIN = 11;
const int MIN_SERVO_PIN  = 10;

//Calibraton! measure how long it takes for the servos to make one fill circle, and input in ms.
const unsigned long FULL_ROTATION_HOUR_MS = 1200; 
const unsigned long FULL_ROTATION_MIN_MS  = 1200; 

const int SERVO_STOP = 90;
const int SERVO_RUN  = 105; //If running backwards, change to 75.

Servo hourServo;
Servo minServo;

unsigned long lastTick = 0;
int minuteCounter = 0;

void setup() {
  hourServo.attach(HOUR_SERVO_PIN);
  minServo.attach(MIN_SERVO_PIN);

  // Start the clock with two hands at 12.
  hourServo.write(SERVO_STOP);
  minServo.write(SERVO_STOP);
  
  delay(1000);
  lastTick = millis();
}

void loop() {
  if (millis() - lastTick >= 60000) {
    lastTick += 60000;
    minuteCounter++;

    stepServo(minServo, FULL_ROTATION_MIN_MS / 60);

    if (minuteCounter >= 12) {
      stepServo(hourServo, FULL_ROTATION_HOUR_MS / 60);
      minuteCounter = 0;
    }
  }
}

void stepServo(Servo &s, unsigned long durationMs) {
  if (durationMs == 0) return;
  s.write(SERVO_RUN);
  delay(durationMs);
  s.write(SERVO_STOP);
}