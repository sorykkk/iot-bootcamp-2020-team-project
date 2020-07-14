#include "extern_variables.h"//conteaza si ordinea introducerii bibliotecilor//in cazul bibliotecii extern_variables.h unde se declar variabilile externe
#include "ultrasonic.h"
#include "keypad_lcd.h"
#include "temp.h"
#include "pump.h"
#include "buzzer.h"
#include "pir.h"
#include "blynk_implementation.h"

//---Extern-variables-definition(global)----------------------------------------------------
unsigned int setted_distance = 0;
unsigned int setted_temp = 0;
bool input_permision = false;//permite inputul la temperatura doar daca a fost introdusa distanta
bool program_state   = false;//porneste si stinge anumite functionalitati a programei
//------------------------------------------------------------------------------------------

//---Time-management------------------------------------------------------------------------
unsigned long start_millis;
unsigned long current_millis;
const unsigned long show_time = 1000;//1 sec
//------------------------------------------------------------------------------------------

//---Ultrasonic-----------------------------------------------------------------------------
unsigned int current_distance = 0;
unsigned int initial_distance = 0;
static int distance = 0;
//-----------------------------------------------------------------------------------------

//---Temperature---------------------------------------------------------------------------
unsigned int current_temp = 0;
//-----------------------------------------------------------------------------------------

//---PIR-----------------------------------------------------------------------------------
bool pir_state = false;
//-----------------------------------------------------------------------------------------

void InputValues(void)
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

  while(input_permision)//pana cand nu se introduce distanta, temperatura nu va putea fi introdusa
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

void CancelProcess(void)
{
  InitializeWithZeroGlobalVariables();
  
  lcd.clear();
  lcd.print("PROCESS CANCELED");
  delay(1000);
}

void CheckCancelProcess(void)
{
  char cancel = mkeypad.getKey();
  if(cancel == 'C')
    CancelProcess();
}

void FinishProcess(int dist, unsigned int temp)
{
  if(dist >= (int)setted_distance && setted_distance && setted_temp)// ==
  {
    BlynkNotify(temp);
  
    InitializeWithZeroGlobalVariables();

    lcd.clear();
    lcd.print("PROCESS FINISHED");
    PrintVirtualLCD();

    while(!pir_state)
    {
      ActivateBuzzer();
      pir_state = DetectMotion();
    }

    pir_state = false;
    delay(1000);
  }
}

void ActivatePumps(void)
{
//pumps logic
//--------------------------------------------------------------
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

int visual_distance(void)//detectarea distantei reale, prin aflarea deltei dintre initial_distance si current_distance
{
  int distance = initial_distance - current_distance;
  if(distance < 0)//daca ultrasonicul isi va mari current_distance in loc sa o micsoreze, distance oricum va fi 0
    distance = 0;

 return distance;
}

void ProcessByProgramState(void)
{
  if(!program_state)
    InputValues();//input pentru setted_temp and setted_distance

  current_millis = millis();
  if(program_state)
  {
    ActivatePumps();
    
    if(current_millis - start_millis >= show_time)
    {
      PrintCurrentTemperature(current_temp);
      start_millis = current_millis;
    }
    
    VirtualCancel();//porneste virtual button pentru cancel daca main program lucreaza
    CheckCancelProcess();//se termina fortat procesul in caz ca este apasata litera 'C'
    FinishProcess(distance, current_temp);
  }

}

void ReadDataFromSensors(void)
{
  //---Get-Started-Values-------------------------
  current_temp = (unsigned int)GetTemperature();
  current_distance = (unsigned int)GetDistance();
  distance = visual_distance();
  //----------------------------------------------
}

void InitializeWithZeroGlobalVariables(void)
{
    setted_distance = 0;
    setted_temp = 0;
    distance = 0;
    input_permision = false;
    program_state = false;

    start_millis = 0;
    current_millis = 0;

    PumpsOff();//cand se va face program_state = false, se va duce automat in InputValues unde este while si deci nu se vor putea opri pompele dupa program_state
}

void BlynkProcesses(void)
{
  BlynkRunProcess();//ruleaza proiectul care interactioneaza cu blynk app
  PrintVirtualLCD();//afiseaza starea fluxului de apa in blynk app
}

void setup()
{
  //---Init-sensors------------------------------
  InitLCDStartPhase();
  InitTemperature();
  initial_distance = (unsigned int)GetDistance();//se ia distanta initiala fara apa pt a verifica prin diferenta care este inaltimea efectiva la care se ridica apa
  InitPumps();
  InitBuzzer();
  InitPIR();
  //---------------------------------------------
  
  InitBlynk();//initializarea WiFi cu blynk app

  analogReadResolution(10);//setarea bit resolution standarta al arduino destinata pentru analog input pentru esp32 
  start_millis = millis();
  
  Serial.begin(115200);//pt debugging
}

void loop()
{
  ReadDataFromSensors();
  BlynkProcesses();
  ProcessByProgramState();
 
  //---Debugging-------------------------------------------------------------------------
  debugging(false);
  //-------------------------------------------------------------------------------------
}

void debugging(bool debug_status)
{
  if(debug_status)
  { 
    Serial.print("Setted distance: ");
    Serial.println(setted_distance);
    Serial.print("Setted temperature: ");
    Serial.println(setted_temp);
  
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print("Initial distance: ");
    Serial.println(initial_distance);
    Serial.print("Current temperature: ");
    Serial.println(current_temp);
    Serial.print("CURRENT DIST: ");
    Serial.println(current_distance);
  
    Serial.println();
    delay(200);
  }
}
