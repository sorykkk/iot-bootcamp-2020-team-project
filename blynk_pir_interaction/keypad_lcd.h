//#include <Keypad.h>
//#include <LiquidCrystal_I2C.h>
#include "extern_variables.h"

#ifndef _KEYPAD_LCD_
#define _KEYPAD_LCD_

//---LCD---------------------------------------------------------------------------------
const int DIST_LENGTH_LIMIT = 3;
const int DIST_MAX_LIMIT = 40;
const int DIST_MIN_LIMIT = 0;

const int TEMP_LENGTH_LIMIT = 2;
const int TEMP_MAX_LIMIT = 100;
const int TEMP_MIN_LIMIT = 20;

unsigned int CountNumberOfDigits(unsigned int);
void InitialDisplay(char);
void InitLCDStartPhase(void);
void PrintGeneralDistanceInfo(unsigned int);
void PrintGeneralTemperatureInfo(unsigned int);
//----------------------------------------------------------------------------------------

//---Keypad-------------------------------------------------------------------------------
const byte ROWS = 4;
const byte COLS = 4;

unsigned int GetKeypadValue(unsigned int, char);
//----------------------------------------------------------------------------------------


#endif
