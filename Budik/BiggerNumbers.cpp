#include <Arduino.h>
#include "BiggerNumbers.h"
#include "lcd_wrapper.h"

byte leftSide[8] = 
{
  B00111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B00111
};
byte upperBar[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte rightSide[8] =
{
  B11100,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11100
};
byte leftEnd[8] =
{
  B01111,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00111
};
byte lowerBar[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte rightEnd[8] =
{
  B11110,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11100
};
byte middleBar[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte lowerEnd[8] = 
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00111,
  B01111
};

void BigNumbersInit()
{
    lcd_createChar(0,leftSide);
    lcd_createChar(1,upperBar);
    lcd_createChar(2,rightSide);
    lcd_createChar(3,leftEnd);
    lcd_createChar(4,lowerBar);
    lcd_createChar(5,rightEnd);
    lcd_createChar(6,middleBar);
    lcd_createChar(7,lowerEnd);
}

void cislo_0(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(0);
  lcd_write(1);
  lcd_write(2);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(0);
  lcd_write(4);
  lcd_write(2);
 }

void cislo_1(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(2);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(2);
}
void cislo_2(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(3);
  lcd_write(6);
  lcd_write(2);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(0);
  lcd_write(4);
  lcd_write(4);  
}
void cislo_3(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(3);
  lcd_write(6);
  lcd_write(2);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(7);
  lcd_write(4);
  lcd_write(2);  
}
void cislo_4(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(0);
  lcd_write(4);
  lcd_write(2);
  lcd_set_cursor(riadok+2,stlpec+1);
  lcd_write(2);
}
void cislo_5(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(0);
  lcd_write(6);
  lcd_write(5);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(7);
  lcd_write(4);
  lcd_write(2);
}
void cislo_6(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(0);
  lcd_write(6);
  lcd_write(5);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(0);
  lcd_write(4);
  lcd_write(2);
}
void cislo_7(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(1);
  lcd_write(1);
  lcd_write(2);
  lcd_set_cursor(riadok+2,stlpec+1);
  lcd_write(2);
}
void cislo_8(int riadok, int stlpec)
{
  lcd_set_cursor(riadok,stlpec);
  lcd_write(0);
  lcd_write(6);
  lcd_write(2);
  lcd_set_cursor(riadok,stlpec+1);
  lcd_write(0);
  lcd_write(4);
  lcd_write(2);
}
void cislo_9(int riadok, int stlpec)
{
   lcd_set_cursor(riadok,stlpec);
   lcd_write(0);
   lcd_write(6);
   lcd_write(2);
   lcd_set_cursor(riadok,stlpec+1);
   lcd_write(7);
   lcd_write(4);
   lcd_write(2);
}

void jednoCiferneCislo(int cislo, int riadok, int stlpec)
{
  switch (cislo) 
        {
      case 0:
        cislo_0(riadok, stlpec);
        break;
      case 1:
        cislo_1(riadok, stlpec);
        break;
      case 2:
        cislo_2(riadok, stlpec);
        break;
      case 3:
        cislo_3(riadok, stlpec);
        break;
      case 4:
        cislo_4(riadok, stlpec);
        break;
      case 5:
        cislo_5(riadok, stlpec);
        break;
      case 6:
        cislo_6(riadok, stlpec);
        break;
      case 7:
        cislo_7(riadok, stlpec);
        break;
      case 8:
        cislo_8(riadok, stlpec);
        break;
      default: 
       cislo_9(riadok, stlpec);
        break;
        }
}
int lcd_PrintBigNumber(int cislo, int riadok, int stlpec, bool dvojbodka)
{
  int riadok2 = riadok;
  if(cislo < 10 && cislo >= 0)
  {
    jednoCiferneCislo(0, riadok2, stlpec);
    riadok2 = riadok2 + 3;
    jednoCiferneCislo(cislo, riadok2, stlpec);
    if(cislo == 1) riadok2++;
    else riadok2 = riadok2 + 3;
  }
  else if (cislo >= 100 || cislo < 0) return;
  else                                                  //Chyba pri 100+
  {
      int rozlozeneCislo[2];                            //Rozlozenie dvojciferneho cisla na mensie
      rozlozeneCislo[0] = cislo / 10;
      rozlozeneCislo[1] = cislo % 10;
      jednoCiferneCislo(rozlozeneCislo[0], riadok2, stlpec);
      
      if(cislo > 9 && cislo < 20) riadok2 = riadok2 + 1;  //Nastavenie medzier medzi 1 a vacsim cislom
      else riadok2 = riadok2 + 3;
      
      jednoCiferneCislo(rozlozeneCislo[1], riadok2, stlpec);

      if(rozlozeneCislo[1] == 1) riadok2 = riadok2 + 1;  //Nastavenie medzier medzi 1 a vacsim cislom
      else riadok2 = riadok2 + 3;
  }
  
  if(dvojbodka == true)                             //Vypisanie dvojbodky
  {
      lcd_set_cursor(riadok2,0);
      lcd_print(".");
      lcd_set_cursor(riadok2,1);
      lcd_print(".");  
  }
  return riadok2;
}

int one_number_counting(int hours, int minutes)
{
  int counter = 0, a = 0, b = 0;
  a = hours / 10;
  b = hours % 10;
  if(a == 1) counter++;
  if(b == 1) counter++;

  a = minutes / 10;
  b = minutes % 10;
  if(a == 1) counter++;
  if(b == 1) counter++;
  return counter;
}

void lcd_PrintTime(int hours, int minutes, bool format)
{
  int riadok, pos = 0;
  bool dvojbodka = true;
  
  if(format == true)
  {
    pos = (one_number_counting(hours, minutes) * 2);
    riadok = lcd_PrintBigNumber(hours, pos,0,dvojbodka);
    riadok++;
    riadok = lcd_PrintBigNumber(minutes,riadok,0,false);
    lcd_set_cursor(riadok,1);
  }
  if(format == false)
  { 
    if(hours > 12)
    {
      pos = (one_number_counting(hours-12, minutes) * 2);
      riadok = lcd_PrintBigNumber(hours-12, pos,0,dvojbodka);
      riadok++;
      riadok = lcd_PrintBigNumber(minutes,riadok,0,false);
      lcd_set_cursor(riadok,1);
      lcd_print("PM");
    }
    if(hours < 12)
    {
      riadok = lcd_PrintBigNumber(hours, pos,0,dvojbodka);
      riadok++;
      riadok = lcd_PrintBigNumber(minutes,riadok,0,false);
      lcd_set_cursor(riadok,1);
      lcd_print("AM");
    }
  }
}
