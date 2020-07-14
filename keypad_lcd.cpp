#include "keypad_lcd.h"
#include "extern_variables.h"

//--------------------------------------------------------------------------------------------------------------
LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte grad[8] =
{
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000
};

unsigned int CountNumberOfDigits(unsigned int n)//returneaza numarul de cifre introdus de pe keypad
{
  int count = 0;
  while(n != 0)
  {
    n /= 10;
    count++;
  }

  return count;
}

bool LengthOfDistance(unsigned int num)
{
  if(CountNumberOfDigits(num) > DIST_LENGTH_LIMIT || (num > DIST_MAX_LIMIT) || (num <= DIST_MIN_LIMIT) || (num >= initial_distance))//(num >= initial_distance/2)
    return false;

  else return true;
}

bool LengthOfTemperature(unsigned int num)
{
  if(CountNumberOfDigits(num) > TEMP_LENGTH_LIMIT || (num > TEMP_MAX_LIMIT) || (num <= TEMP_MIN_LIMIT))
    return false;

  else return true;
}

void InitialDisplay(char nr_of_display)
{
  lcd.setCursor(0, 0);
  if(nr_of_display == 0)//0 pt a face display la ecranul de pornire la distance
  {
    setted_distance = 0;
    lcd.print("GIVE DIST. (cm):");
  }
  if(nr_of_display == 1)//1 pt display la ecranul de pornire a temperaturii
  {
    setted_temp = 0;
    lcd.print("GIVE TEMP. ("); lcd.write((byte)0); lcd.write('C'); lcd.print("):");
  }
  lcd.setCursor(0, 1);//cursorul se muta by default pe a 2 linie a 0 col
}

void InitLCDStartPhase(void)//Se initializeaza lcd, se printeaza prima linie, si cursorul se muta pe a 2 pt tapare
{
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, grad);
  InitialDisplay(0);//se afiseaza de la inceput, pt ca nu a fost apasat nici un buton
}

void PrintSettedKeypadValue(char nr_of_display)//se printeaza valoarea setata
{
  if(nr_of_display == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("SETTED DISTANCE:");
    lcd.setCursor(0, 1);
    lcd.print(setted_distance);
    lcd.setCursor(CountNumberOfDigits(setted_distance)+1, 1);//se numara din cate cifre este compus numarul pt a se lua un spatiu rezerva
    lcd.print("cm");//pentru a se printa unitatea de masura
  }

  if(nr_of_display == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("SETTED TEMP.:");
    lcd.setCursor(0, 1);
    lcd.print(setted_temp);
    lcd.setCursor(CountNumberOfDigits(setted_temp)+1, 1);//se numara din cate cifre este compus numarul pt a se lua un spatiu rezerva
    lcd.write((byte)0); lcd.print("C");
  }
}

void WarningMessage(void)//mesajul in caz ca ceva este introdus incorect
{
  lcd.print("*IVALID VALUE*");
  delay(2000);
}

void PrintGeneralDistanceInfo(unsigned int num)//se efectueaza printarea informatiei despre distanta dupa conditiile din LengthOfValue()
{
  if(LengthOfDistance(num))// se verifica daca satisface cerintele inputului
  {           //nu va permite setarea/afisarea distantei ca 0, dupa apasarea dubla pe '#'
    if(num)
    {
      lcd.clear();
      PrintSettedKeypadValue(0);//se afiseaza valoarea setata
                    //daca dinstance e 0 nu se va efectua nimic, adica nu se va efectua functia WarningMessage();
      delay(2000);
      lcd.clear();
      InitialDisplay(1);
    }
  }

  else
  {
    lcd.clear();
    WarningMessage();
    InitialDisplay(0);
  }
}

void PrintGeneralTemperatureInfo(unsigned int num)//se efectueaza printarea informatiei despre temperatura dupa conditiile din LengthOfValue()
{
  if(LengthOfTemperature(num))// se verifica daca satisface cerintele inputului
  {           //nu va permite setarea/afisarea distantei ca 0, dupa apasarea dubla pe '#'
    if(num)
    {
      lcd.clear();
      PrintSettedKeypadValue(1);
      delay(2000);
      lcd.clear();
    }
  }

  else
  {
    input_permision = true;//daca este introdusa o valoare care nu corespunde cerintelor, se face afisarea "GIVE TEMP." si input_permision devine true pt a se putea introduce din nou doar valoarea temp.
    lcd.clear();
    WarningMessage();
    InitialDisplay(1);
  }
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
char hex_map[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROWS] = {19, 18, 5, 17};
byte pin_cols[COLS] = {16,4, 0, 2};

Keypad mkeypad = Keypad(makeKeymap(hex_map), pin_rows, pin_cols, ROWS, COLS);

unsigned int GetKeypadValue(unsigned int number, char nr_of_switch)
{
  char key = mkeypad.getKey();
  unsigned int compare_num = 0;

  if(key == NO_KEY)
     return number;

  while(key != '#')
  {
    if(nr_of_switch == 0)//pt distanta
      {
        switch (key)
          {
           case NO_KEY: break;

           case '0'...'9':
                 if(!compare_num)//pt a nu se afisa mai '0' de fiecare data cand este apasat// se face initialDisplay() cand number e 0 (adica compare_num)
                   InitialDisplay(0);

                   lcd.print(key);
                   number = number * 10 + (key - '0');
                   compare_num = number;
                   break;

           case '*':
               lcd.clear();
               number = 0;
               InitialDisplay(0);
               break;
          }
      }

      if(nr_of_switch == 1)//pt temperatura
      {
        switch (key)
          {
           case NO_KEY: break;

           case '0'...'9':
                 if(!compare_num)//pt a nu se afisa mai multe '0' de fiecare data cand este apasat
                   InitialDisplay(1);

                   lcd.print(key);
                   number = number * 10 + (key - '0');
                   compare_num = number;
                   break;

           case '*':
             if(number == 0)//daca valoarea temp nu a fost modificata, adica daca a fost deja apasat '*' sau nu s-a introdus nimic si se apasa din nou '*'
             {
               lcd.clear();
               input_permision = false;//la apasarea dubla a '*' se duce la InitialDisplay(0);// afecteaza while(input_permision) cand nu intra in if();//permite intrarea in while-ul cu setarea distantei, ci nu a temp.
               program_state = false; // face ca dupa "*incorect value*" la temp, sa lucreze dublu '*' si sa intoarca la "give dist."//se face ca la urmatoarea iteratie a functiei loop(), cand program_state va fi false sa se efectuieze din nou citirea datelor dist si temp
               InitialDisplay(0);
               return number;//greu se muta din give temp in give dist// se asteapta un delay careva
               break;
             }

             else
             {
               lcd.clear();
               number = 0;
               InitialDisplay(1);
               break;
             }
          }
      }
    key = mkeypad.getKey();
  }

  return number;
}
//--------------------------------------------------------------------------------------------------------------
