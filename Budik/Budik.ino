#include <Arduino.h>
#include "alarm_clock.h"
#include "lcd_wrapper.h"

void setup(){
  lcd_init();
  lcd_clear();
  Serial.begin(9600);
  
  //rtc_init(5, 4);   //Inicializacia času, stači len raz
  /*
  EEPROM.write(50,0);     //Typ zmeny casu
  EEPROM.write(51,0);     //stateOfTime
  EEPROM.write(52,0);     //changeHours
  EEPROM.write(53,0);     //changeMinutes
  EEPROM.write(58,0);     //stateOfDate
  EEPROM.write(59,0);     //stateOfChangeDate
  EEPROM.write(60,0);     //TypeOfDatum
  EEPROM.write(61,0);     //TypeOfTimeChange
  */

  
  int type = EEPROM.read(50);   
  int typeDatum = EEPROM.read(60);   
  
  if(type == 1)
  {
    int hours = EEPROM.read(52); 
    int minutes = EEPROM.read(53);
    int dayofweek = EEPROM.read(54); 
    int dayofmonth = EEPROM.read(55);
    int months = EEPROM.read(56); 
    int years = EEPROM.read(57); 
    rtc_init(minutes, hours, dayofweek, dayofmonth, months, years + 2000);   //Inicializacia času, stači len raz
    type = 0;
    Serial.print("type");
    EEPROM.write(50,type);
    EEPROM.write(52,hours);
    EEPROM.write(53,minutes);

    Serial.print(hours);
    Serial.print(minutes);
  }
  
  if(typeDatum == 1)
  {
    int dayofweek = EEPROM.read(54); 
    int dayofmonth = EEPROM.read(55);
    int months = EEPROM.read(56); 
    int years = EEPROM.read(57);

    int hours = EEPROM.read(52); 
    int minutes = EEPROM.read(53);
    
    rtc_init(minutes, hours, dayofweek, dayofmonth, months, years + 2000);
    typeDatum = 0;
    EEPROM.write(60,typeDatum);
    EEPROM.write(52,hours);
    EEPROM.write(53,minutes);
  }
/*
  EEPROM.write(0,0);    // Main state
  EEPROM.write(1,0);    // Cas format
  EEPROM.write(2,0);    // Temp format

  EEPROM.write(3,0);    // Stopwatch timerMode
  EEPROM.write(4,0.0);    // Stopwatch timeHistory
  EEPROM.write(5,0.0);    // Stopwatch actualTime

  EEPROM.write(6,15);    // countdownTimer casovacSek
  EEPROM.write(7,0);    // countdownTimer casovacMin
  EEPROM.write(8,0);    // countdownTimer stateOfCasovac

  EEPROM.write(9,12);    // alarm_clock budenieHod
  EEPROM.write(10,0);    // alarm_clock budenieMin
  EEPROM.write(11,0);    // alarm_clock stateOfBudenie

  float f = 0.00;
  EEPROM.put(12, f);

  writeStringToEEPROM(13,"===PRIPRAVENY===");
  writeStringToEEPROM(31," ");
  */

}
 
void loop()
{
  machine(); 
}
