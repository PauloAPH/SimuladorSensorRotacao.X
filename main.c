/*
 * File:   main.c
 * Author: aluno
 *
 * Created on 11 de Novembro de 2022, 14:52
 */

#include <xc.h>
#include "config.h"
#include "LCD.h"

#define botao1 PORTEbits.RE0
#define botao2 PORTEbits.RE1

unsigned char dente = 0;
unsigned char i = 0;
unsigned char counter = 0;

unsigned char vetorH[11] = {0xD5, 0xE5, 0xED, 0xF1, 0xF5, 0xF7, 0xF8, 0xFA, 0xFB, 0xFC, 0xFC};
unsigned char vetorL[11] = {0xCF, 0x6F, 0x3F, 0xEF, 0x0F, 0x4A, 0xF7, 0x44, 0x4F, 0x29, 0xDF};
unsigned char vetorH2[11] = {0x78, 0xA6, 0xBE, 0xCC, 0xD5, 0xDC, 0xE1, 0xE5, 0xE8, 0xEB, 0xED};
unsigned char vetorL2[11] = {0x0E, 0xEE, 0x5E, 0x6E, 0xCF, 0x81, 0x87, 0x6F, 0x8F, 0x1D, 0x3F};
unsigned int vetor_rotacao[11] = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000};

unsigned char frase[] = "Rotacao:    RPM";

/*Funcoo de tratamento de Interrupcoes*/
void __interrupt() ISR() {
    /*Verifica se a Interrupecao que ocorreu foi relativa ao Timer 0*/
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        INTCONbits.TMR0IE = 0;

        if (PORTBbits.RB0 == 0) {
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            TMR0H = 0xFB;
            TMR0L = 0x4E;
            INTCONbits.TMR0IE = 1;
        } else if (PORTBbits.RB0 == 1) {
            if (dente < 58) {
                LATBbits.LATB0 = 0;
                LATBbits.LATB1 = 0;
                TMR0H = vetorH[i];
                TMR0L = vetorL[i];
                INTCONbits.TMR0IE = 1;
                dente++;
            } else {
                LATBbits.LATB0 = 0;
                LATBbits.LATB1 = 0;
                TMR0H = vetorH2[i];
                TMR0L = vetorL2[i];
                INTCONbits.TMR0IE = 1;
                dente = 0;
            }
        }
    }
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        counter++;
        if (counter == 5) {
            if (botao1 == 0) {
                i++;
                if (i > 10) {
                    i = 10;
                }
            }
            if (botao2 == 0) {
                if (i > 0) {
                    i--;
                }
            }
            counter = 0;
            TMR1H = 0x00;
            TMR1L = 0x00;
        }
    }
}

/*Inicializacao de Hardware do Microcontrolador*/
void init_hw() {

    /*Configura as portas do microcontrolador*/
    TRISA = 0;
    TRISB = 0;
    PORTB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0xFF;

    /*Configura Timer 0*/
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.TMR0ON = 1;
    INTCONbits.TMR0IE = 1;

    /*Configura Timer 1*/
    T1CONbits.RD16 = 1;
    T1CONbits.T1RUN = 1;
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;
    PIE1bits.TMR1IE = 1;

    /*Habilita Interrupcao global e dos perifericos */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    /*Desliga o Conversor A/D e configura todas as portas como digitais*/
    ADCON0bits.ADON = 0;
    ADCON1 = 0b00001111;
}

void main() {

    init_hw();
    __delay_ms(50);

    init_lcd();
    __delay_ms(50);

    comando(0x80);
    escreve_frase(frase, 16);

    while (1) {
        comando(0x89);
        escreve_inteiro(vetor_rotacao[i]);
    }
}