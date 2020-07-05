#ifndef _BUZZER_H_
#define _BUZZER_H_

//to do: a short melody that will be at repeat until the motion sensor isn't triggered

const int BUZZER_PIN = 14;
const int BUZZER_FREQ = 100;//50

void InitBuzzer();
void ActivateBuzzer();

#endif
