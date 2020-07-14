#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

const int TRIG_PIN = 25;
const int ECHO_PIN = 26;

float GetDistance(void);
float GetInitialDistance(void);

#endif
