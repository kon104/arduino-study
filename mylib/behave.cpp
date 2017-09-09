#include "behave.h"

void behavePower(int vcc, int gnd)
{
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);  
}

