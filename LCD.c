/*
 * File:   LCD.c
 * Author: aluno
 *
 * Created on 16 de Março de 2023, 16:04
 */

#include "LCD.h"
#include "config.h"

/*Envia um comando para o LCD*/
void comando(unsigned char dado) {

    RS_LCD = 0;
    RW_LCD = 0;
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = (dado & 0x10) >> 4;
    D5_LCD = (dado & 0x20) >> 5;
    D6_LCD = (dado & 0x40) >> 6;
    D7_LCD = (dado & 0x80) >> 7;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = (dado & 0x01);
    D5_LCD = (dado & 0x02) >> 1;
    D6_LCD = (dado & 0x04) >> 2;
    D7_LCD = (dado & 0x08) >> 3;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;
}

/*Envia um caracter para o LCD*/
void escrita(unsigned char dado) {

    RS_LCD = 1;
    RW_LCD = 0;
    E_LCD = 0;
    __delay_us(20);

    D4_LCD = (dado & 0x10) >> 4;
    D5_LCD = (dado & 0x20) >> 5;
    D6_LCD = (dado & 0x40) >> 6;
    D7_LCD = (dado & 0x80) >> 7;

    E_LCD = 1;
    __delay_us(20);
    E_LCD = 0;
    __delay_us(20);

    D4_LCD = (dado & 0x01);
    D5_LCD = (dado & 0x02) >> 1;
    D6_LCD = (dado & 0x04) >> 2;
    D7_LCD = (dado & 0x08) >> 3;

    E_LCD = 1;
    __delay_us(20);
    E_LCD = 0;
}

/*Fun��o de Inicializa��o do LCD*/
void init_lcd() {
    __delay_ms(15);

    RS_LCD = 0;
    RW_LCD = 0;
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = 1;
    D5_LCD = 1;
    D6_LCD = 0;
    D7_LCD = 0;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;
    __delay_ms(5);
    RS_LCD = 0;
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = 1;
    D5_LCD = 1;
    D6_LCD = 0;
    D7_LCD = 0;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;
    __delay_us(100);
    RS_LCD = 0;
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = 1;
    D5_LCD = 1;
    D6_LCD = 0;
    D7_LCD = 0;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;
    RS_LCD = 0;
    E_LCD = 0;
    __delay_us(10);

    D4_LCD = 0;
    D5_LCD = 1;
    D6_LCD = 0;
    D7_LCD = 0;

    E_LCD = 1;
    __delay_us(10);
    E_LCD = 0;

    comando(0x28);
    __delay_us(40);
    comando(0x06);
    __delay_us(40);
    comando(0x0E);
    __delay_us(40);
    __delay_us(40);
    comando(0x01);
}

/*Funcao para Escrita de uma string no LCD */
void escreve_frase(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        escrita(*data);
        data++;
    }
}

/*Converte um inteiro com sinal ou sem sinal em uma string que sera escrita no 
LCD*/
void escreve_inteiro(unsigned int x) {

    unsigned char vetor_aux[] = "0000";
    unsigned int x_aux = x;
    unsigned char j;

    for (j = 0; j < 4; j++) {
        vetor_aux[4 - j] = (x_aux % 10) + 0x30;
        x_aux = x_aux / 10;
    }
    escreve_frase(vetor_aux, 4);
}