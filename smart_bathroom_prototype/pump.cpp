#include "pump.h"
#include <Arduino.h>

void InitPumps()
{
  pinMode(HOT_PUMP, OUTPUT);
  pinMode(COLD_PUMP, OUTPUT);
}

void HotPumpOn()
{
  digitalWrite(HOT_PUMP, HIGH);
}

void HotPumpOff()
{
  digitalWrite(HOT_PUMP, LOW);
}

void ColdPumpOn()
{
  digitalWrite(COLD_PUMP, HIGH);
}

void ColdPumpOff()
{
  digitalWrite(COLD_PUMP, LOW);
}

void PumpsOff()
{
  ColdPumpOff();
  HotPumpOff();
}
