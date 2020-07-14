#include "buzzer.h"
#include <Arduino.h>

void InitBuzzer()
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void ActivateBuzzer()
{
  unsigned char i;

  for(i = 0; i < BUZZER_FREQ; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(10);
    digitalWrite(BUZZER_PIN, LOW);
    delay(10);
  }

  delay(500);
}
