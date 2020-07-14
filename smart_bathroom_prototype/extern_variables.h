#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#ifndef _EXTERN_VAR_
#define _EXTERN_VAR_

//---Extern-used-variables-declaration--------------------------------------------------
extern int unsigned  setted_distance;
extern unsigned int setted_temp;
extern unsigned int initial_distance;

extern bool input_permision;
extern bool program_state;
//---------------------------------------------------------------------------------------

//---Extern-used-objects-declaration-----------------------------------------------------
extern LiquidCrystal_I2C lcd;
extern Keypad mkeypad;
extern byte grad[8];
//---------------------------------------------------------------------------------------

//---Extern-used-functions-declaration---------------------------------------------------
extern void CancelProcess(void);
extern int visual_distance(void);
//---------------------------------------------------------------------------------------

#endif
