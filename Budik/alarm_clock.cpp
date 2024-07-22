#include "alarm_clock.h"
#include "lcd_wrapper.h"
#include "BiggerNumbers.h"

dht DHT;
virtuabotixRTC myRTC(7, 8, 9);

void rtc_init(uint8_t minutes, uint8_t hours, uint8_t dayofweek, uint8_t dayofmonth, uint8_t months, int years)   //Inicializacia datumu a casu
{
  //myRTC.setDS1302Time(0, 29, 23, 5, 22, 04, 2022);
  myRTC.setDS1302Time(0, minutes, hours, dayofweek, dayofmonth, months, years);
}

void sound()    //Zvuk budika
{
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(500);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
}

String dayChoosing(int dayOFweek)    //Podla dňa v týždni vypíše slovo  
{
  if (dayOFweek == 1) return "Pondelok";
  if (dayOFweek == 2) return "Utorok";
  if (dayOFweek == 3) return "Streda";
  if (dayOFweek == 4) return "Stvrtok";
  if (dayOFweek == 5) return "Piatok";
  if (dayOFweek == 6) return "Sobota";
  if (dayOFweek == 7) return "Nedela";
}

int daysInMonth(int months, int years)    
{
  bool isLeap = false;
  if(years % 4 == 0) isLeap = true;
  if (months == 1) return 31;
  if (months == 2) 
  {
    if(isLeap == true) return 29;
    else return 28;
  }
  if (months == 3) return 31;
  if (months == 4) return 30;
  if (months == 5) return 31;
  if (months == 6) return 30;
  if (months == 7) return 31;
  if (months == 8) return 31;
  if (months == 9) return 30;
  if (months == 10) return 31;
  if (months == 11) return 30;
  if (months == 12) return 31;
}

void countdownTimer()   //Časovač
{
  String znakCasovac = readStringFromEEPROM(13);
  int casovacSek = EEPROM.read(6), casovacMin = EEPROM.read(7), stateOfCasovac = EEPROM.read(8);

  lcd_clear();
  lcd_set_cursor(0, 1);
  lcd_print(znakCasovac);

  lcd_set_cursor(0, 0);
  lcd_print(" Casovac: ");
  lcd_print_int_better(casovacMin);
  lcd_print(":");
  lcd_print_int_better(casovacSek);

  delay(500);
  if ((digitalRead(BTN_ENTER_PIN) == 0) && (stateOfCasovac == 0))
  {
    if (digitalRead(BTN_2_PIN) != 0)
    {
      casovacMin++;
      EEPROM.write(7, casovacMin);
    }
    if (digitalRead(BTN_3_PIN) != 0)
    {
      casovacSek++;
      if (casovacSek == 60) casovacSek = 0;
      EEPROM.write(6, casovacSek);
    }
  }
  if (digitalRead(BTN_ENTER_PIN) != 0)
  {
    if (stateOfCasovac == 0)
    {
      stateOfCasovac = 1;
      znakCasovac = "=====ZACATY=====";
      writeStringToEEPROM(13, znakCasovac);
      EEPROM.write(8, stateOfCasovac);
    }
    else
    {
      stateOfCasovac = 0;
      EEPROM.write(8, stateOfCasovac);
      znakCasovac = "===PRIPRAVENY===";
      writeStringToEEPROM(13, znakCasovac);
      noTone(buzzer);
    }

  }
  if (stateOfCasovac == 1)
  {
    casovacSek--;
    if ((casovacSek < 0) && (casovacMin > 0))
    {
      casovacSek = 60;
      casovacMin--;
    }
    EEPROM.write(7, casovacMin);
    EEPROM.write(6, casovacSek);
    if ((casovacSek < 0) && (casovacMin == 0))
    {
      znakCasovac = "====SKONCENY====";
      writeStringToEEPROM(13, znakCasovac);
      sound();
      casovacSek = 0;
      EEPROM.write(6, casovacSek);
    }
    delay(500);
  }
}

void alarm_clock()
{
  String znak = readStringFromEEPROM(31);
  int snooze = 5;
  int budenieHod = EEPROM.read(9), budenieMin = EEPROM.read(10), stateOfBudenie = EEPROM.read(11);

  lcd_clear();
  lcd_set_cursor(15, 0);
  lcd_print(znak);

  lcd_set_cursor(0, 1);
  myRTC.updateTime();
  lcd_print("Cas: ");
  lcd_print_int_better(myRTC.hours);
  lcd_print(":");
  lcd_print_int_better(myRTC.minutes);
  lcd_print(":");
  lcd_print_int_better(myRTC.seconds);

  lcd_set_cursor(0, 0);
  lcd_print("Budik: ");
  lcd_print_int_better(budenieHod);
  lcd_print(":");
  lcd_print_int_better(budenieMin);
  delay(1000);

  if ((digitalRead(BTN_ENTER_PIN) == 0) && (stateOfBudenie == 0))
  {
    if (digitalRead(BTN_2_PIN) != 0)
    {
      budenieHod++;
      if (budenieHod == 24) budenieHod = 0;
      EEPROM.write(9, budenieHod);
    }
    if (digitalRead(BTN_3_PIN) != 0)
    {
      budenieMin++;
      if (budenieMin == 60) budenieMin = 0;
      EEPROM.write(10, budenieMin);
    }
  }
  if (digitalRead(BTN_ENTER_PIN) != 0)
  {
    if (stateOfBudenie == 0)
    {
      stateOfBudenie = 1;
      EEPROM.write(11, stateOfBudenie);
      znak = "#";
      writeStringToEEPROM(31, znak);
    }
    else
    {
      stateOfBudenie = 0;
      EEPROM.write(11, stateOfBudenie);
      znak = " ";
      writeStringToEEPROM(31, znak);
      noTone(buzzer);
    }
  }
  if (digitalRead(BTN_3_PIN) != 0)
  {
    noTone(buzzer);
    if (stateOfBudenie == 1)
    {
      budenieMin = budenieMin + snooze;
      if (budenieMin >= 60) budenieMin = budenieMin - 60;
      EEPROM.write(10, budenieMin);
    }
  }
  if (stateOfBudenie == 1)
  {
    if ((budenieHod == myRTC.hours) && (budenieMin == myRTC.minutes))
    {
      sound();
      stateOfBudenie == 0;
      EEPROM.write(11, stateOfBudenie);
    }
  }
}

float temp_to_farenheit(float temp)
{
  float farenheit;
  farenheit = ((temp * 1.8) + 32);
  return farenheit;
}

void temp_hum()
{
  DHT.read11(dht_apin);    //grab 40-bit data packet from DHT sensor
  float temp = DHT.temperature;
  float hum = DHT.humidity;
  int format =  EEPROM.read(2);
  lcd_set_cursor(0, 0);
  lcd_print("Teplota: ");

  if (format == 0)
  {
    lcd_print(DHT.temperature);
    lcd_print("C");
  }

  if (format == 1)
  {
    temp = temp_to_farenheit(temp);
    lcd_print(temp);
    lcd_print("F");
  }

  if (digitalRead(BTN_2_PIN) != 0)
  {
    format++;
    if (format == 2) format = 0;
    EEPROM.write(2, format);
  }
  lcd_set_cursor(0, 1);
  lcd_print("Vlhkost: ");
  lcd_print(hum);
  lcd_print("%");

  delay(1000);
  lcd_clear();
}


void cas()
{
  int format =  EEPROM.read(1);
  int stateOfTime = EEPROM.read(51), changeHours =  EEPROM.read(52), changeMinutes =  EEPROM.read(53);
  lcd_clear();
  myRTC.updateTime();

  if (stateOfTime == 1)
  {
    int typeOfTimeChange = EEPROM.read(61);

    switch (typeOfTimeChange) 
    {
      case 0:
        lcd_set_cursor(15,0);
        lcd_print("H");
        if (digitalRead(BTN_2_PIN) != 0)
        {
          changeHours++;
          if (changeHours == 24) changeHours = 0;
          EEPROM.write(52, changeHours);
        }
        if (digitalRead(BTN_3_PIN) != 0)
        {
          changeHours--;
          if (changeHours == -1) changeHours = 24;
          EEPROM.write(52, changeHours);
        }
        break;
      default:
        lcd_set_cursor(15,0);
        lcd_print("M");
        if (digitalRead(BTN_2_PIN) != 0)
        {
          changeMinutes++;
          if (changeMinutes == 60) changeMinutes = 0;
          EEPROM.write(53, changeMinutes);
        }
        if (digitalRead(BTN_3_PIN) != 0)
        {
          changeMinutes--;
          if (changeMinutes == -1) changeMinutes = 59;
          EEPROM.write(53, changeMinutes);
        }
        break;
    }
    
    if (digitalRead(BTN_ENTER_PIN) != 0)
    {
      if(typeOfTimeChange == 2)
      {
        typeOfTimeChange = 0;
        stateOfTime = 0;
        EEPROM.write(51,stateOfTime);
        EEPROM.write(61,typeOfTimeChange);
        asm volatile ("jmp 0");
      }
      typeOfTimeChange++;
      EEPROM.write(61,typeOfTimeChange);
    }
    lcd_PrintTime(changeHours, changeMinutes, true);
  }
  if (stateOfTime == 0)
  {
    if (format == 0)
    {
      lcd_PrintTime(myRTC.hours, myRTC.minutes, true);
    }
    else
    {
      lcd_PrintTime(myRTC.hours, myRTC.minutes, false);
    }
    if (digitalRead(BTN_2_PIN) != 0)
    {
      format++;
      if (format == 2) format = 0;
      EEPROM.write(1, format);
    }
    if (digitalRead(BTN_ENTER_PIN) != 0)
    {
      EEPROM.write(52, myRTC.hours); 
      EEPROM.write(53, myRTC.minutes);
      int type = 1;
      stateOfTime = 1;
      int dayofweek = myRTC.dayofweek, dayofmonth = myRTC.dayofmonth, months = myRTC.month, years = (myRTC.year - 2000);
      EEPROM.write(51, stateOfTime);
      EEPROM.write(50, type);
      EEPROM.write(54, dayofweek);
      EEPROM.write(55, dayofmonth);
      EEPROM.write(56, months);
      EEPROM.write(57, years);
    }
  }
  delay(1000);
}

void datum()
{
  int stateOfDatum = EEPROM.read(58);
  
  if(stateOfDatum == 0)
  {
    lcd_clear();
    myRTC.updateTime();
    lcd_set_cursor(0, 0);
    lcd_print(dayChoosing(myRTC.dayofweek));
    lcd_set_cursor(0, 1);
    lcd_print_int_better(myRTC.dayofmonth);
    lcd_print("-");
    lcd_print_int_better(myRTC.month);
    lcd_print("-");
    lcd_print_int_better(myRTC.year - 2000);
    if (digitalRead(BTN_ENTER_PIN) != 0)
    {
      stateOfDatum = 1;
      EEPROM.write(58, stateOfDatum);     
      int typeOfDatum = EEPROM.read(60);
      typeOfDatum = 1;
      EEPROM.write(60,typeOfDatum);
    
    }
    delay(1000);
  }
  if(stateOfDatum == 1)
  {
    int stateOfDateChange = EEPROM.read(59);
    int dayOfweek = EEPROM.read(54);
    int dayofmonth = EEPROM.read(55);
    int months = EEPROM.read(56);
    int years = EEPROM.read(57);
    
    lcd_clear();
    lcd_set_cursor(0,0);
    lcd_print(dayChoosing(dayOfweek));
    lcd_print(" ");
    lcd_set_cursor(8,1);
    lcd_print_int_better(dayofmonth);
    lcd_print("-");
    lcd_print_int_better(months);
    lcd_print("-");
    lcd_print_int_better(years);
    
    if (digitalRead(BTN_ENTER_PIN) != 0)
        {
          stateOfDateChange++;
          if(stateOfDateChange == 4) 
          {
            stateOfDateChange = 0;
            stateOfDatum = 0;
            EEPROM.write(58, stateOfDatum);
            EEPROM.write(59, stateOfDateChange);
            int hours = myRTC.hours;
            int minutes = myRTC.minutes;
            EEPROM.write(52,hours);
            EEPROM.write(53,minutes);
            asm volatile ("jmp 0");
          }
          EEPROM.write(59, stateOfDateChange);
        }
        
    switch (stateOfDateChange) {
      case 0:
        lcd_set_cursor(0,1);
        lcd_print("#");
        if (digitalRead(BTN_2_PIN) != 0)
        {
          dayOfweek++;
          if (dayOfweek == 8) dayOfweek = 1;
          EEPROM.write(54, dayOfweek);
        }
        break;
      case 1:
        lcd_set_cursor(15,0);
        lcd_print("#");
        if (digitalRead(BTN_2_PIN) != 0)
        {
          years++;
          if(years == 100 ) years = 0;
          EEPROM.write(57, years);
        }
        if (digitalRead(BTN_3_PIN) != 0)
        {
          years--;
          if(years == -1 ) years = 99;
          EEPROM.write(57, years);
        }
        break;
      case 2:
        lcd_set_cursor(12,0);
        lcd_print("#");
        if (digitalRead(BTN_2_PIN) != 0)
        {
          months++;
          if(months == 13 ) years = 0;
          EEPROM.write(56, months);
        }
        if (digitalRead(BTN_3_PIN) != 0)
        {
          months--;
          if(months == -1 ) months = 12;
          EEPROM.write(56, months);
        }
        break;
      default:
        lcd_set_cursor(9,0);
        lcd_print("#");
        int moths = EEPROM.read(56);
        int years = EEPROM.read(57);
        int dayCounter = daysInMonth(moths, years);
        if (digitalRead(BTN_2_PIN) != 0)
        {
          dayofmonth++;
          if(dayofmonth == dayCounter + 1 ) dayofmonth = 1;
          EEPROM.write(55, dayofmonth);
        }
        if (digitalRead(BTN_3_PIN) != 0)
        {
          dayofmonth--;
          if(dayofmonth == 0 ) dayofmonth = dayCounter;
          EEPROM.write(55, dayofmonth);
        }
        break;
}
    delay(1000);
  }
  
}

void stopwatch()
{
  long timerMode = EEPROM.read(3);
  long startTime;
  float actualTime = 0.00;
  EEPROM.get(12, actualTime);
  float timeHistory = EEPROM.get(4, timeHistory);

  lcd_set_cursor(0, 1);
  lcd_print("Posledny: ");
  lcd_print(timeHistory);
  lcd_set_cursor(0, 0);
  lcd_print("Stopky: ");
  if (digitalRead(BTN_ENTER_PIN) != 0)
  {
    startTime = millis();
    timerMode++;
    EEPROM.write(3, timerMode);
    delay(400);
  }
  if (timerMode == 1)
  {
    actualTime = (millis() - startTime) / 1000.0;
    EEPROM.put(12, actualTime);
    lcd_print(actualTime);
  }
  if (timerMode > 1)
  {
    timerMode = 0;
    timeHistory = actualTime;
    actualTime = 0.0;
    EEPROM.put(12, actualTime);
    EEPROM.write(3, timerMode);
    EEPROM.put(4, timeHistory);
  }
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}



void machine()
{
  int state = EEPROM.read(0);

  if (digitalRead(BTN_1_PIN) != 0)
  {
    state++; 
    EEPROM.write(0, state);
  }

  switch (state)
  {
    case 0:
      stopwatch();
      break;
    case 1:
      cas();
      break;
    case 2:
      datum();
      break;
    case 3:
      temp_hum();
      break;
    case 4:
      alarm_clock();
      break;
    case 5:
      countdownTimer();
      break;
    default:
      state = 0;
      EEPROM.write(0, state);
      lcd_clear();
      delay(400);
      break;
  }
}
