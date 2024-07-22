#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H

#include <Arduino.h>
#include "dht.h"
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define dht_apin A1 // Analog Pin sensor is connected to
#define BTN_1_PIN       3
#define BTN_2_PIN       4
#define BTN_3_PIN       5
#define BTN_ENTER_PIN   A0
#define buzzer     10


/**
 * Inicializuje RTC
 * 
 * Vždy ked potrebujete inicializovať časový modul.
 * Táto funkcia sa volá len raz v setup() a nastavuje sa tam čas.
 */

void rtc_init(uint8_t minutes, uint8_t hours, uint8_t dayofweek, uint8_t dayofmonth, uint8_t months, int years);
void temp_hum();
void datum();
void cas();
void alarm_clock();
void machine();
void stopwatch();
void sound();
String dayChoosing(int dayOFweek);
void countdownTimer();
float temp_to_farenheit(float temp);
int daysInMonth(int months, int years);

void writeStringToEEPROM(int addrOffset, const String &strToWrite);
String readStringFromEEPROM(int addrOffset);


//ooverloading 

#endif
