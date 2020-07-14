#ifndef _TEMP_H_
#define _TEMP_H_

const int TEMP_PIN = 35;

void InitTemperature(void);
float GetTemperature(void);
void PrintCurrentTemperature(unsigned int);


#endif
