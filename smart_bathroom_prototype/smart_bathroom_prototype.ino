#include "dd_pump/pump.h"
#include "dd_ultrasonic/ultrasonic.h"
#include "dd_ds18b20_temp/temp.h"
#include "dd_keypad/keypad_lcd.h"

//---Global-Variables---------------------------------------------------------
unsigned int setted_distance = 0;
unsigned int setted_temp = 0;
bool input_permision = false;//permite inputul la temperatura doar daca a fost introdusa distanta
bool program_state  = false;//porneste si stinge anumite functionalitati a programei
//----------------------------------------------------------------------------

//---Ultrasonic----------------------------------------------------------------
unsigned int current_distance = 0;
unsigned int current_temp = 0;
unsigned int initial_distance = 0;
//-----------------------------------------------------------------------------

void setup()
{
	InitLCDStartPhase();
	InitTemperature();
	initial_distance = (unsigned int)GetInitialDistance();//se ia distanta initiala fara apa pt a verifica prin diferenta care este inaltimea efectiva la care se ridica apa
	Serial.begin(9600);
}

void loop()
{

	current_temp = (unsigned int)GetTemperature();
	current_distance = (unsigned int)GetDistance();

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

	if(/*setted_distance && setted_temp && */program_state)//problema ca trebuie un hold time mai mare pt ca sa dovedeasca sa citeasca caracterul
	{
		char cancel = mkeypad.getKey();
		if(cancel == 'C')
		{
			setted_distance = 0;
			setted_temp = 0;
			input_permision = false;
			program_state = false;
			lcd.clear();
			lcd.print("PROCESS CANCELED");
			delay(1000);
		}
		//else program_state = true;//linie aditionala/neobligatorie, pt safety
	}

	if(/*setted_distance && setted_temp &&*/ program_state)
		PrintCurrentTemperature(current_temp);

//-------------------------------------------------------------------------------------
	Serial.print("Setted distance: ");
	Serial.println(setted_distance);
	Serial.print("Setted temperature: ");
	Serial.println(setted_temp);

	int distance = initial_distance - current_distance;

	if(distance < 0)//daca ultrasonicul isi va mari current_distance in loc sa o micsoreze, distance oricum va fi 0
		distance = 0;

	Serial.print("Current distance: ");
	Serial.println(distance);
	Serial.print("Initial distance: ");
	Serial.println(initial_distance);
	Serial.print("Current Ultra: ");
	Serial.println(current_distance);

	Serial.println();
//-------------------------------------------------------------------------------------
}
