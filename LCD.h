/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

/*Prototipos das fun�oes do arquivo LCD.c*/
#define RS_LCD LATDbits.LATD1
#define E_LCD  LATDbits.LATD0
#define RW_LCD LATDbits.LATD2
#define D7_LCD LATDbits.LATD7
#define D6_LCD LATDbits.LATD6
#define D5_LCD LATDbits.LATD5
#define D4_LCD LATDbits.LATD4

void comando(unsigned char dado);
void escrita(unsigned char dado);
void init_lcd();
void escreve_frase(unsigned char *data, int length);
void escreve_inteiro(unsigned int x);