#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

const int TRIG_PIN = 34;
const int ECHO_PIN = 36;

double GetDistance(void);
double GetInitialDistance(void);

#endif
