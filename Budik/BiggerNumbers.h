#ifndef BiggerNumbers_h
#define BiggerNumbers_h

/**
 * Inicializácia vytvorených znakov
 */
void BigNumbersInit();

/**
 * Vypísanie kompletného čisla
 * 
 * Vypíše na konkretnom mieste na displeji veľké čislo
 */
int lcd_PrintBigNumber(int cislo, int riadok, int stlpec,  bool dvojbodka);

/**
 * Vypísanie jednociferného čísla
 * 
 * Vypíše na konkretnom mieste jednociferné číslo
 */
void jednoCiferneCislo(int cislo, int riadok, int stlpec);

/**
 * Počet jednotiek v čase
 * 
 * Funkcia vypočíta počet jednotiek v čisle hodin a minut.
 */
int one_number_counting(int hours, int minutes);

/**
 * Vypísanie hodin a minut
 * 
 * Vypíše na konkretnom mieste na displeji čas vo zvolenom formáte
 */
void lcd_PrintTime(int hours, int minutes, bool format);

/**
 * Vytváranie čísel
 * 
 * Vytvorí veľké čislo na danej pozícií
 */
void cislo_0(int riadok, int stlpec);
void cislo_1(int riadok, int stlpec);
void cislo_2(int riadok, int stlpec);
void cislo_3(int riadok, int stlpec);
void cislo_4(int riadok, int stlpec);
void cislo_5(int riadok, int stlpec);
void cislo_6(int riadok, int stlpec);
void cislo_7(int riadok, int stlpec);
void cislo_8(int riadok, int stlpec);
void cislo_9(int riadok, int stlpec);


#endif
