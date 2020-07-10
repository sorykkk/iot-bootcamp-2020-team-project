#include "extern_variables.h"//conteaza si ordinea introducerii bibliotecilor//in cazul bibliotecii extern_variables.h unde se declar variabilile externe
#include "ultrasonic.h"
#include "keypad_lcd.h"
#include "temp.h"
#include "pump.h"
#include "buzzer.h"
#include "pir.h"
#include "blynk_interaction.h"

//---Extern-variables-definition(global)----------------------------------------------------
unsigned int setted_distance = 0;
unsigned int setted_temp = 0;
bool input_permision = false;//permite inputul la temperatura doar daca a fost introdusa distanta
bool program_state   = false;//porneste si stinge anumite functionalitati a programei
//----------------------------------------------------------------------------

//---Global-variable-used-only-once-in-this-scope-------------------------------------------
bool process_finished = false;
//------------------------------------------------------------------------------------------

//---Ultrasonic----------------------------------------------------------------
unsigned int current_distance = 0;
unsigned int initial_distance = 0;
//-----------------------------------------------------------------------------

//---Temperature---------------------------------------------------------------
unsigned int current_temp = 0;
//-----------------------------------------------------------------------------

//---PIR-----------------------------------------------------------------------
bool pir_state = false;
//-----------------------------------------------------------------------------

void InputValues()
{
  if(!program_state)
  {
    while(!setted_distance)
    {

      setted_distance = GetKeypadValue(setted_distance, 0);

      if(setted_distance)
      {
        input_permision = true;
        PrintGeneralDistanceInfo(setted_distance);
      }

      else
      {
        input_permision = false;
        InitialDisplay(0);
      }
    }

    while(input_permision)
    {
      setted_temp = GetKeypadValue(setted_temp, 1);

      if(setted_temp)
      {
        input_permision = false;//folosit inaintea functiei in caz ca la PrintGeneralTemperatureInformation va fi true;
        program_state = true;
        PrintGeneralTemperatureInfo(setted_temp);
      }

      else InitialDisplay(1);
    }
  }
}

void CancelProcess()
{
  setted_distance = 0;
  setted_temp = 0;
  input_permision = false;
  program_state = false;

  PumpsOff(); // trebuie pt ca cand se va face program_state = false, se va duce automat in InputValues unde este wile si deci nu se vor putea opri pompele dupa program_state
  
  lcd.clear();
  lcd.print("PROCESS CANCELED");
  delay(1000);
}

void IfCancelProcess()
{
  if(program_state)//problema ca trebuie un hold time mai mare pt ca sa dovedeasca sa citeasca caracterul
  {
    char cancel = mkeypad.getKey();
    if(cancel == 'C')
      CancelProcess();

    //else program_state = true;//linie aditionala/neobligatorie, pt safety
  }
}

void FinishProcess(int dist, unsigned int temp)
{
  if(program_state)
  {
    if(dist >= (int)setted_distance)// ==
    {
      BlynkNotify(temp);
    
      setted_distance = 0;
      setted_temp = 0;
      input_permision = false;
      program_state = false;

      PumpsOff();// trebuie pt ca cand se va face program_state = false, se va duce automat in InputValues unde este wile si deci nu se vor putea opri pompele dupa program_state

      lcd.clear();
      lcd.print("PROCESS FINISHED");
      PrintVirtualLCD();

      while(!pir_state)
      {
        BlynkRunProcess();
        
        ActivateBuzzer();
        pir_state = DetectMotion();
        VirtualPir();
      }

      pir_state = false;
      delay(1000);
    }
  }
}

void ActivatePumps()
{
//pumps logic
//--------------------------------------------------------------
  if(program_state)
  {
    if(current_temp <= setted_temp)//chiar daca temperatura curenta este egala cu temperatura setata pompa oricum va pompa apa calda
    {
      ColdPumpOff();
      HotPumpOn();
    }
    if(current_temp > setted_temp)
    {
      HotPumpOff();
      ColdPumpOn();
    }
  }
}

int visual_distance()//detect real distance with ultrasonic initial and current distance
{
  int distance = initial_distance - current_distance;
  if(distance < 0)//daca ultrasonicul isi va mari current_distance in loc sa o micsoreze, distance oricum va fi 0
    distance = 0;

 return distance;
}

void setup()
{
  //---Init-sensors------------------------------
  InitLCDStartPhase();
  InitTemperature();
  initial_distance = (unsigned int)GetDistance();//GetInitialDistance();//se ia distanta initiala fara apa pt a verifica prin diferenta care este inaltimea efectiva la care se ridica apa
  InitPumps();
  InitBuzzer();
  InitPIR();
  //---------------------------------------------
  
  InitBlynk();//initialize wifi with blynk app
}

void loop()
{
  analogReadResolution(10);//set standart arduino bit resolution destinated to analog input for esp32

  //---Get-Started-Values-------------------------
  current_temp = (unsigned int)GetTemperature();
  current_distance = (unsigned int)GetDistance();
  int distance = visual_distance();
  //----------------------------------------------

  InputValues();//input for setted_temp and setted_distance

  BlynkRunProcess();//run the process that interact with blynk app

  /**/ActivatePumps();//problem with lcd, caused by pumps power supply

  PrintCurrentTemperature(current_temp);
  
  VirtualCancel();//run virtual button of cancel if the main program is running
  PrintVirtualLCD();
  
  IfCancelProcess();//se termina fortat procesul in caz ca este apasata litera 'C'
  FinishProcess(distance, current_temp);

//---Debugging-------------------------------------------------------------------------
//  Serial.print("Setted distance: ");
//  Serial.println(setted_distance);
//  Serial.print("Setted temperature: ");
//  Serial.println(setted_temp);
//
//  Serial.print("Distance: ");
//  Serial.println(distance);
//  Serial.print("Initial distance: ");
//  Serial.println(initial_distance);
//  Serial.print("Current temperature: ");
//  Serial.println(current_temp);
//  Serial.print("CURRENT DIST: ");
//  Serial.println(current_distance);

//  Serial.println();
//  delay(500);
//-------------------------------------------------------------------------------------
}
