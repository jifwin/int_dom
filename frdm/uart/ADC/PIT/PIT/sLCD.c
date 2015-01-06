#include "MKL46Z4.h"
#include "sLCD.h"

// Zmienne tworzace dwie tablice
const static uint8_t LCD_Front_Pin[LCD_N_FRONT] = {LCD_FRONT0, LCD_FRONT1, LCD_FRONT2, LCD_FRONT3, LCD_FRONT4, LCD_FRONT5, LCD_FRONT6, LCD_FRONT7};
const static uint8_t LCD_Back_Pin[LCD_N_BACK] = {LCD_BACK0, LCD_BACK1, LCD_BACK2, LCD_BACK3};


void sLCD_Err(void)
{
	sLCD_Init();
		//E
	LCD->WF8B[LCD_Front_Pin[0]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G); 
	LCD->WF8B[LCD_Front_Pin[1]] = (LCD_S_A); 
	//r
	LCD->WF8B[LCD_Front_Pin[2]] = (LCD_S_E | LCD_S_G);
	LCD->WF8B[LCD_Front_Pin[3]];
	//r
LCD->WF8B[LCD_Front_Pin[4]] = (LCD_S_E | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[5]];
	
}
	

void counter(void)
{
	int min, min2, sec, sec2;
	min = 0; min2 = 0; sec = 0; sec2 = 0;
	
	sLCD_Init();
	sLCD_set(0,1);
	sLCD_set(0,2);
	sLCD_set(0,3);
	sLCD_set(0,4);
	sLCD_dots(4);	
	
	
	
	
	while(1)
	{
		
		sec++;
		wait(1);
		if(sec > 9)
		{
		sec = 0; sec2++;
			if(sec2 > 5)
			{
				sec2=0;
				min++;
			}
				if(min>9)
				{
					min =0;
					min2++;
				}
					if(min2>9)
					{
						min2=0;
					}						
		}	
		sLCD_set(min2,1);
		sLCD_set(min,2);
		sLCD_set(sec2,3);
		sLCD_set(sec,4);
	}
}

void wait(uint8_t time)
{
	int cnt = 0;
	while(1)
	{
		cnt++;
		if(cnt > time*6000000)
		{
			cnt = 0;
			break;
		}
	}
	
}
void sLCD_convert(uint16_t value, uint8_t type)
{
	//sLCD_Init();
	if(type == 1)
	{
		sLCD_set(value%10, 4);
		sLCD_set((value/10)%10,3);
		sLCD_set((value/100)%10,2);
		sLCD_set(value/1000,1);
	}
	else if(type == 2)
	{
		if(value <16)
		{
			switch(value){
				case 0: { sLCD_set(0,1); sLCD_set(0,2); sLCD_set(0,3); sLCD_set(0,4); break; }
				case 1: { sLCD_set(0,1); sLCD_set(0,2); sLCD_set(0,3); sLCD_set(1,4); break;}
				case 2: { sLCD_set(0,1); sLCD_set(0,2); sLCD_set(1,3); sLCD_set(0,4); break;}
				case 3: { sLCD_set(0,1); sLCD_set(0,2); sLCD_set(1,3); sLCD_set(1,4); break;}
				case 4: { sLCD_set(0,1); sLCD_set(1,2); sLCD_set(0,3); sLCD_set(0,4); break;}
				case 5: { sLCD_set(0,1); sLCD_set(1,2); sLCD_set(0,3); sLCD_set(1,4); break;}
				case 6: { sLCD_set(0,1); sLCD_set(1,2); sLCD_set(1,3); sLCD_set(0,4); break;}
				case 7: { sLCD_set(0,1); sLCD_set(1,2); sLCD_set(1,3); sLCD_set(1,4); break;}
				case 8: { sLCD_set(1,1); sLCD_set(0,2); sLCD_set(0,3); sLCD_set(0,4); break;}
				case 9: { sLCD_set(1,1); sLCD_set(0,2); sLCD_set(0,3); sLCD_set(1,4); break;}
				case 10: { sLCD_set(1,1); sLCD_set(0,2); sLCD_set(1,3); sLCD_set(0,4);break;}
				case 11: { sLCD_set(1,1); sLCD_set(1,2); sLCD_set(1,3); sLCD_set(1,4);break;}
				case 12: { sLCD_set(1,1); sLCD_set(1,2); sLCD_set(0,3); sLCD_set(0,4);break;}
				case 13: { sLCD_set(1,1); sLCD_set(1,2); sLCD_set(0,3); sLCD_set(1,4);break;}
				case 14: { sLCD_set(1,1); sLCD_set(1,2); sLCD_set(1,3); sLCD_set(0,4);break;}
				case 15: { sLCD_set(1,1); sLCD_set(1,2); sLCD_set(1,3); sLCD_set(1,4);break;}
				default: break;}
		}
	}	
	
	else if(type==3)
	{
		int digit1;
		int digit2;
		digit2 = value % 16;
		digit1 = value / 16;
		

		sLCD_set(digit1, 3);
		sLCD_set(digit2, 4);
		}
	
	else if(type ==4)
	{
		int digit1;
		int digit2;
		digit2 = value % 8;
		digit1 = value / 8;
		
		
		sLCD_set(digit1, 3);
		sLCD_set(digit2, 4);
		
	}
	
	else 
	{
		sLCD_Err();
	}
	
}

void sLCD_dots(uint8_t digit)
{
if ( digit > 0 & digit < 5)
{
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] ;
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] +=
(LCD_S_DEC);
}

}
	
void sLCD_set(uint16_t value,uint8_t digit){
// value – wyswietlana wartosc,
// digit – pozycja na której ma byc wyswietlona wartosc
	
if(value <= 0x0F & digit <= 4) 
{

if(value==0x00){ // aby wyswietlic ‘0’ zapalamy segmenty
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = // D, E, F oraz A, B, C
(LCD_S_D | LCD_S_E |LCD_S_F); // (patrz tabelki w zadaniu 2.1)
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] =
(LCD_S_A | LCD_S_B | LCD_S_C);
}
else if(value==0x01){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] =
(LCD_C);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] =
(LCD_S_B | LCD_S_C);
}
else if(value==0x02){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_G | LCD_S_E | LCD_S_D);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_A);
}
else if(value==0x03){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_G | LCD_S_D);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_A | LCD_S_C);
}
else if(value==0x04){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_C);
}
else if(value==0x05){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G | LCD_S_D);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_C);
}
else if(value==0x06){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G | LCD_S_E | LCD_S_D);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_C);
}
else if(value==0x07){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_C);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
}
else if(value==0x08){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
}
else if(value==0x09){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
}
else if(value==0x0A){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_E | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
}
else if(value==0x0B){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_C);
}
else if(value==0x0C){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A);
}
else if(value==0x0D){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_C);
}
else if(value==0x0E){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A);
}
else if(value==0x0F){
LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_E | LCD_S_F | LCD_S_G);
LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A);
}
}

else 
{
sLCD_Err();

}

}


void sLCD_Init(void)
	{
	// konfiguracja zegara dla portów wykorzystywanych przy obsludze wyswietlacza
	// i modulu sLCD
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_SLCD_MASK;
	// wstepne wylaczenie i reset kontrolera
	LCD->GCR |= LCD_GCR_PADSAFE_MASK; // safe state on output control pins
	LCD->GCR &= ~LCD_GCR_LCDEN_MASK; // Clear LCDEN w trakcie konfiguracji
	// konfiguracja multiplekserów do operacji portów jako kontroler LCD
	PORTD->PCR[0] = PORT_PCR_MUX(0u);
	PORTE->PCR[4] = PORT_PCR_MUX(0u);
	PORTB->PCR[23] = PORT_PCR_MUX(0u);
	PORTB->PCR[22] = PORT_PCR_MUX(0u);
	PORTC->PCR[17] = PORT_PCR_MUX(0u);
	PORTB->PCR[21] = PORT_PCR_MUX(0u);
	PORTB->PCR[7] = PORT_PCR_MUX(0u);
	PORTB->PCR[8] = PORT_PCR_MUX(0u);
	PORTE->PCR[5] = PORT_PCR_MUX(0u);
	PORTC->PCR[18] = PORT_PCR_MUX(0u);
	PORTB->PCR[10] = PORT_PCR_MUX(0u);
	PORTB->PCR[11] = PORT_PCR_MUX(0u);
	
	// konfiguracja rejestrów LCD
	LCD->GCR = // !!!!!!
	LCD_GCR_RVTRIM(0x00) |
	LCD_GCR_CPSEL_MASK |
	LCD_GCR_LADJ(0x03) |
	LCD_GCR_VSUPPLY_MASK |
	LCD_GCR_ALTDIV(0x00) |
	LCD_GCR_SOURCE_MASK |
	LCD_GCR_LCLK(0x01) |
	LCD_GCR_DUTY(0x03);
	// konfiguracja migania wyswietlacza
	LCD->AR = LCD_AR_BRATE(0x03); // !!!!!!
	// konfiguracja rejestru FDCR
	LCD->FDCR = 0x00000000; // !!!!!!
	// aktywowanie 12 pinów do kontroli wyswietlaczem (dwa rejestry po 32 bity)
	LCD->PEN[0] =
	LCD_PEN_PEN(1u<<7 ) | // LCD_P7
	LCD_PEN_PEN(1u<<8) 	|
	LCD_PEN_PEN(1u<<10) |
	LCD_PEN_PEN(1u<<11) |
	LCD_PEN_PEN(1u<<18) |
	LCD_PEN_PEN(1u<<17) |
	LCD_PEN_PEN(1u<<19);

	LCD->PEN[1] =
	LCD_PEN_PEN(1u<<8) 	|
	LCD_PEN_PEN(1u<<20) |
	LCD_PEN_PEN(1u<<5) 	|
	LCD_PEN_PEN(1u<<21) |
	LCD_PEN_PEN(1u<<6);

	// skonfigurowanie 4 pinów plaszczyzny tylnej (dwa rejestry po 32 bity)
	LCD->BPEN[0] =
	LCD_BPEN_BPEN(1u<<18) |
	LCD_BPEN_BPEN(1u<<19);
	LCD->BPEN[1] =
	LCD_BPEN_BPEN(1u<<8) |
	LCD_BPEN_BPEN(1u<<20);
	// konfiguracja rejestrów przebiegów (Waveform register) – 4 aktywne, reszta nie
	// konfiguracja polega na równomiernym rozlozeniu faz, w tym przypadku 4, na 8 bitach
	// (44.3.7 w KL46 Reference Manual)
	LCD->WF[0] =
	LCD_WF_WF0(0x00) |
	LCD_WF_WF1(0x00) |
	LCD_WF_WF2(0x00) |
	LCD_WF_WF3(0x00);
	LCD->WF[1] =
	LCD_WF_WF4(0x00) |
	LCD_WF_WF5(0x00) |
	LCD_WF_WF6(0x00) |
	LCD_WF_WF7(0x00);
	LCD->WF[2] =
	LCD_WF_WF8(0x00) |
	LCD_WF_WF9(0x00) |
	LCD_WF_WF10(0x00) |
	LCD_WF_WF11(0x00);
	LCD->WF[3] =
	LCD_WF_WF12(0x00) |
	LCD_WF_WF13(0x00) |
	LCD_WF_WF14(0x00) |
	LCD_WF_WF15(0x00);
	LCD->WF[4] =
	LCD_WF_WF16(0x00) |
	LCD_WF_WF17(0x00) |
	LCD_WF_WF18(0x88) | // COM3 (10001000)
	LCD_WF_WF19(0x44); // COM2 (01000100)
	LCD->WF[5] =
	LCD_WF_WF20(0x00) |
	LCD_WF_WF21(0x00) |
	LCD_WF_WF22(0x00) |
	LCD_WF_WF23(0x00);
	LCD->WF[6] =
	LCD_WF_WF24(0x00) |
	LCD_WF_WF25(0x00) |
	LCD_WF_WF26(0x00) |
	LCD_WF_WF27(0x00);
	LCD->WF[7] =
	LCD_WF_WF28(0x00) |
	LCD_WF_WF29(0x00) |
	LCD_WF_WF30(0x00) |
	LCD_WF_WF31(0x00);
	LCD->WF[8] =
	LCD_WF_WF32(0x00) |
	LCD_WF_WF33(0x00) |
	LCD_WF_WF34(0x00) |
	LCD_WF_WF35(0x00);
	LCD->WF[9] =
	LCD_WF_WF36(0x00) |
	LCD_WF_WF37(0x00) |
	LCD_WF_WF38(0x00) |
	LCD_WF_WF39(0x00);
	LCD->WF[10] =
	LCD_WF_WF40(0x11) | // COM0 (00010001)
	LCD_WF_WF41(0x00) |
	LCD_WF_WF42(0x00) |
	LCD_WF_WF43(0x00);
	LCD->WF[11] =
	LCD_WF_WF44(0x00) |
	LCD_WF_WF45(0x00) |
	LCD_WF_WF46(0x00) |
	LCD_WF_WF47(0x00);
	LCD->WF[12] =
	LCD_WF_WF48(0x00) |
	LCD_WF_WF49(0x00) |
	LCD_WF_WF50(0x00) |
	LCD_WF_WF51(0x00);
	LCD->WF[13] =
	LCD_WF_WF52(0x22) | // COM1 (00100010)
	LCD_WF_WF53(0x00) |
	LCD_WF_WF54(0x00) |
	LCD_WF_WF55(0x00);
	LCD->WF[14] =
	LCD_WF_WF56(0x00) |
	LCD_WF_WF57(0x00) |
	LCD_WF_WF58(0x00) |
	LCD_WF_WF59(0x00);
	LCD->WF[15] =
	LCD_WF_WF60(0x00) |
	LCD_WF_WF61(0x00) |
	LCD_WF_WF62(0x00) |
	LCD_WF_WF63(0x00);
	// koniec konfiguracji, wiec clear PADSAFE i wlaczenie wyswietlacza
	LCD->GCR &= ~LCD_GCR_PADSAFE_MASK; // disable save state
	LCD->GCR |= LCD_GCR_LCDEN_MASK; // wlaczenie wyswietlacza
}
	
int display_number(uint16_t value, uint8_t format) {
    //0 - bin
    //1 - oct
    //2 - dec
    //3 - hex
	uint32_t tab[4] = {0,0,0,0};
	uint32_t dzielnik = 0;
	uint32_t i = 0;
   
    switch(format) {
        case 0:
						dzielnik = 2;
            if (value > 15) {
                return 1;
            }
            break;
           
            case 1: 
						dzielnik = 8;
            if (value > 4095) { // zmienic na octalny
                return 1;
            }
            break;
           
            case 2:
						dzielnik = 10;
            if (value > 9999) {
                return 1;
            }
            break;
           
            case 3:
						dzielnik = 0x10;
            if (value > 0xFFFF) {
                return 1;
            }
            break;
           
            default: 
						
						break;
    }
   


for(i = 4; i > 0; i--) {
	
	tab[i-1] = value%dzielnik;
	value = value/dzielnik;
	sLCD_set(tab[i-1], i);
	
}
	
return 0;
}

void display_error()
{
		sLCD_set(0x0E, 1);
		sLCD_set(0x0A, 2);
		sLCD_set(0x00, 3);
		sLCD_set(0x0A, 4);
}
