#ifndef _PUMP_H_
#define _PUMP_H_

const int HOT_PUMP = 23;
const int COLD_PUMP = 27;

void InitPumps();
void HotPumpOn();
void HotPumpOff();
void ColdPumpOn();
void ColdPumpOff();
void PumpsOff();

#endif
