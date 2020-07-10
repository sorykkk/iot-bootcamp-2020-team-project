#include "temp.h"
#include "keypad_lcd.h"
#include "extern_variables.h"
#include <Arduino.h>

void InitTemperature() { pinMode(TEMP_PIN, INPUT); }

float GetTemperature()
{
  int tempReading =analogRead(TEMP_PIN);
  double tempK = log(10000.0 * ((1024.0 / tempReading -1)));
  tempK = 1 /(0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  float tempC = tempK - 273.15;

  return tempC;
}

void PrintCurrentTemperature(unsigned int num)
{
  lcd.setCursor(0, 0);
  lcd.print("CURRENT TEMP:");
  lcd.setCursor(0, 1);
  lcd.print(num);
  lcd.setCursor(CountNumberOfDigits(num)+1, 1);
  lcd.write((byte)0); lcd.print("C");
}
