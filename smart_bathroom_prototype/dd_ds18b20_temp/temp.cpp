#include "temp.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "../dd_keypad/keypad_lcd.h"

OneWire oneWire(TEMP_PIN);
DallasTemperature sensor(&oneWire);

void InitTemperature() { sensor.begin(); }

float GetTemperature()
{
	sensor.requestTemperatures();
	return (sensor.getTempCByIndex(0));
}

void PrintCurrentTemperature(unsigned int num)
{
	lcd.setCursor(0, 0);
	lcd.print("CURRENT TEMP:");
	lcd.setCursor(0, 1);
	lcd.print(num);
	lcd.setCursor(CountNumberOfDigits(setted_temp)+1, 1);
	lcd.write((byte)0); lcd.print("C");
}
