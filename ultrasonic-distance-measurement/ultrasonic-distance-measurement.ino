/**
 * 
 * Reffer to url below about HC-SR04(module of ultrasonic distance mesurement).
 * http://akizukidenshi.com/download/ds/sainsmar/hc-sr04_ultrasonic_module_user_guidejohn_b.pdf
 */

#include "behave.h"

#define VCCPIN 10
#define GNDPIN 11
#define TRIGPIN 8
#define ECHOPIN 9

// Trigger is a time to send a ultrasonic to measure a distance.
#define TRIGGER 10

// The coef of speed is 58.0 in case of cm or 148 in case of inch.
#define COEFSPEED 58.0

void setup() {
  Serial.begin(9600);
  Serial.println("[begin]: setup()");

  behavePower(VCCPIN, GNDPIN);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  Serial.println("[end]: setup()");
}

float measureDistance(int trigpin, int echopin, int trigtime, float coef)
{
  int during;
  float distance;

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(trigtime);
  digitalWrite(trigpin, LOW);
  during = pulseIn(echopin, HIGH);
  distance = (float) during / coef;
  return distance;
}

void loop() {
  float distance;
  distance = measureDistance(TRIGPIN, ECHOPIN, TRIGGER, COEFSPEED);
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
