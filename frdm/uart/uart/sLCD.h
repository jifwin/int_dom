#include "MKL46Z4.h"


// zdefiniowanie ilosci pin?w na poszczeg?lnych plaszczyznach
#define LCD_N_FRONT 8
#define LCD_N_BACK 4
// Makra dla segment?w, kazdy znak sterowany jest przez dwa piny
// Pin 1 -> (Digit*2 - 1), Pin 2 -> Digit*2
// Pin 1 Pin 2
// COM0 D Dec
// COM1 E C
// COM2 G B
// COM3 F A
#define LCD_S_D 0x11 // segment D
#define LCD_S_E 0x22 // segment E
#define LCD_S_G 0x44 // segment G
#define LCD_S_F 0x88 // segment F
#define LCD_S_DEC 0x11
#define LCD_S_C 0x22
#define LCD_S_B 0x44
#define LCD_S_A 0x88
#define LCD_C 0x00 // clear
// Makra dla kazdego pinu
#define LCD_FRONT0 37u
#define LCD_FRONT1 17u
#define LCD_FRONT2 7u
#define LCD_FRONT3 8u
#define LCD_FRONT4 53u
#define LCD_FRONT5 38u
#define LCD_FRONT6 10u
#define LCD_FRONT7 11u
#define LCD_BACK0 40u
#define LCD_BACK1 52u
#define LCD_BACK2 19u
#define LCD_BACK3 18u
// Zmienne tworzace dwie tablice

void sLCD_set(uint16_t value,uint8_t digit);
void sLCD_Err(void);
void sLCD_Init(void);

void sLCD_dots(uint8_t digit);

void sLCD_convert(uint16_t value, uint8_t type);

void wait(uint8_t value);

void counter(void);
int display_number(uint16_t value, uint8_t format);