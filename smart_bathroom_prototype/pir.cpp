#include "pir.h"
#include <Arduino.h>

void InitPIR(void)
{
  pinMode(PIR_PIN, INPUT);
}

bool DetectMotion(void)
{
  if(digitalRead(PIR_PIN))
    return true;

  else return false;
}
