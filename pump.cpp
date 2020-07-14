#include "pump.h"
#include <Arduino.h>

void InitPumps(void)
{
  pinMode(HOT_PUMP, OUTPUT);
  pinMode(COLD_PUMP, OUTPUT);
}

void HotPumpOn(void)
{
  digitalWrite(HOT_PUMP, HIGH);
}

void HotPumpOff(void)
{
  digitalWrite(HOT_PUMP, LOW);
}

void ColdPumpOn(void)
{
  digitalWrite(COLD_PUMP, HIGH);
}

void ColdPumpOff(void)
{
  digitalWrite(COLD_PUMP, LOW);
}

void PumpsOff(void)
{
  ColdPumpOff();
  HotPumpOff();
}
