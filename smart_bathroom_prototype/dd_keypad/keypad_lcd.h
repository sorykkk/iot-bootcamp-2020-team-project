#include <Keypad.h>
#include <LiquidCrystal.h>

#ifndef _KEYPAD_LCD_
#define _KEYPAD_LCD_

//---Extern-used-variables--------------------------------------------------------------
extern int unsigned	setted_distance;
extern int unsigned	setted_temp;
extern unsigned int initial_distance;
extern bool 		input_permision;
extern bool 		program_state;
//---------------------------------------------------------------------------------------

//---LCD---------------------------------------------------------------------------------
const int DIST_LENGTH_LIMIT = 3;
const int DIST_MAX_LIMIT    = 100;
const int DIST_MIN_LIMIT    = 0;

const int TEMP_LENGTH_LIMIT = 2;
const int TEMP_MAX_LIMIT    = 54;
const int TEMP_MIN_LIMIT    = 20;

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
extern LiquidCrystal lcd;

unsigned int CountNumberOfDigits(unsigned int);
void InitialDisplay(char);
void InitLCDStartPhase(void);
void PrintGeneralDistanceInfo(unsigned int);
void PrintGeneralTemperatureInfo(unsigned int);
//----------------------------------------------------------------------------------------

//---Keypad-------------------------------------------------------------------------------
const byte ROWS = 4;
const byte COLS = 4;

extern byte grad[8];

extern Keypad mkeypad;

unsigned int GetKeypadValue(unsigned int, char);
//----------------------------------------------------------------------------------------


#endif