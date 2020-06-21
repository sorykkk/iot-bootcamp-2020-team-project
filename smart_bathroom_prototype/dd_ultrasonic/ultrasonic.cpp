#include "ultrasonic.h"
#include <HCSR04.h>

UltraSonicDistanceSensor distance_sensor(TRIG_PIN, ECHO_PIN);

double GetDistance(void)
{
	return (distance_sensor.measureDistanceCm());
}

double GetInitialDistance(void)
{
	return (distance_sensor.measureDistanceCm());
}
