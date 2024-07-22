#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"
LiquidCrystal_I2C lcd(0x27,16,2);


void lcd_init()
{
  lcd.init(); 
  lcd.backlight();
}

void lcd_clear()
{
  lcd.clear();
}

void lcd_set_cursor(int y, int x)
{
  lcd.setCursor(y, x);
}

void lcd_print(char text){
    lcd.print(text);
}

void lcd_print(float text){
    lcd.print(text);
}

void lcd_print(double text){
    lcd.print(text);
}

void lcd_print(String text){
    lcd.print(text);
}

void lcd_print(int text){
    lcd.print(text);
}

void lcd_print_int_better(int number){
    if(number < 10)
    {
      lcd.print(0);
      lcd.print(number);
      }
    else
    {
      lcd.print(number);
    }
}

void lcd_write(char text)
{
  lcd.write(text);
  }

void lcd_createChar(int number, byte names)
{
  if(number > 8 || number < 0) return;
  lcd.createChar(number,names);  
}
