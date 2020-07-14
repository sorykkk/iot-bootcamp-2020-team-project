#ifndef _PUMP_H_
#define _PUMP_H_

const int HOT_PUMP = 23;
const int COLD_PUMP = 27;

void InitPumps(void);
void HotPumpOn(void);
void HotPumpOff(void);
void ColdPumpOn(void);
void ColdPumpOff(void);
void PumpsOff(void);

#endif
