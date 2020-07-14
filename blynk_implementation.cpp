#include "blynk_implementation.h"
#include "extern_variables.h"
#include "temp.h"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

//nu pot fi incluse in header pt ca se folosesc ca argumente pt functiile incluse in custom functii care vor fi inlcuse in source file, adica se multiplica declararea variabililor si compilatorul nu stie care sa o foloseasca, pt a preveni asta trebuie declarate extern in .h si definite in alt modul
//---WiFi-Info-----------------------------------------------------------------------------
char *auth = "6Shubi9hflK0GvXdhAK_Tun0lvj6gllp";
char *ssid = "Orange-Tekwill";
char *pass = "";
//------------------------------------------------------------------------------------------

BlynkTimer timer;

//Virtual lcd init
//------------------------------------------------------------------------------------------
WidgetLCD virtual_lcd(V10);
//------------------------------------------------------------------------------------------

//Virtual pump button init
//------------------------------------------------------------------------------------------
bool pump_button_state;
BLYNK_CONNECTED(){ Blynk.syncVirtual(V1); }
BLYNK_WRITE(V1){ pump_button_state = param.asInt(); }
//------------------------------------------------------------------------------------------

void BlynkNotify(unsigned int current_temp)
{
  Blynk.notify(String("Bathroom is ready!\nTemperature: ") + current_temp);
  Blynk.email("SmartBathroom", "Your bathroom is ready!");
}

void send_sensor()//Inscrierea in blynk app a telemetriei
{
  Blynk.virtualWrite(V5, GetTemperature());
  Blynk.virtualWrite(V6, map(visual_distance(), 0, setted_distance, 0, 1023));
}

void InitBlynk(void)
{
  WiFi.begin(ssid, pass);
  
  //---Init-Blynk-app----------------------------
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, send_sensor);
  //---------------------------------------------
}

void VirtualCancel(void)
{
  if(pump_button_state)
    CancelProcess();
}

void PrintVirtualLCD(void)//printarea informatiei despre water flow pe virtual lcd widget
{
  virtual_lcd.print(3, 0, "WATER FLOW");
  
  if(program_state)
    virtual_lcd.print(7, 1, "ON ");
    
  else virtual_lcd.print(7, 1, "OFF");
}

void BlynkRunProcess(void)
{
  //---Run-Blynk-app-----------------------------
  Blynk.run();
  timer.run();
  //--------------------------------------------
}
