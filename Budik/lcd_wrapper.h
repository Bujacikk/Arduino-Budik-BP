#ifndef LCD_WRAPPER_H
#define LCD_WRAPPER_H

/**
 * Inicializuje LCD
 * 
 * Vždy ked potrebujete inicializovať displej.
 * Táto funkcia sa volá v setup().
 */
void lcd_init();


/**
 * Vyčistí LCD displej
 * 
 * Vyčisti obsah LCD displeja. Po zavolaní je displej prázdny.
 */
void lcd_clear();


/**
 * Uloží kurzor na presnú pozíciu
 * 
 * Nastaví kurzor na presnú pozíciu podla osi x a y
 * @parameter y je riadok
 * @parameter x je stĺpec
 */
void lcd_set_cursor(int y, int x);


/**
 * Vypíše text na LCD displej.
 * 
 * Vypíše vstup na lcd displej na pozíciu kurzora
 * 
 * @parametrom je text na vypísanie
 */
void lcd_print(char text);
void lcd_print(float text);
void lcd_print(double text);
void lcd_print(String text);
void lcd_print(int text);
void lcd_print_int_better(int number);

/**
 * Vypíše znak na LCD displej.
 * 
 * @parametrom je znak na vypísanie
 */
void lcd_write(char text);

/**
 * Vytvorí špeciany znak
 * 
 * Vytvorí špecialny znak ktorý sme nakreslili v matici.
 */
void lcd_createChar(int number, byte names);


#endif
