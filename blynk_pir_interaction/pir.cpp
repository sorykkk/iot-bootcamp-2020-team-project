#include "pir.h"
#include <Arduino.h>

void InitPIR()
{
  pinMode(PIR_PIN, INPUT);
}

bool DetectMotion()
{
  if(digitalRead(PIR_PIN))
    return true;

  else return false;
}
