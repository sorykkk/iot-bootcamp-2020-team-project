#include "../dd_pump/pump.h"

#include "Arduino.h"

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
	digitalWrite(COLD_PUMP, HIGH);
}

void PumpsOff()
{
	ColdPumpOff();
	HotPumpOff();
}
