/*
 * TWI_Header.h
 *
 * Created: 17/01/2018 14:35:44
 *  Author: Henrique
 */ 
#include <avr/io.h>
#include "serial.h"
#define AGUARDO_TWI 200				// se o aguardo for maior que 200 vezes ocorreu um erro
// definições dos protótipos do Two Wire Interface
void initTWI(void);
uint8_t TwiStart(uint8_t);
void TwiStop(void);
int  TwiReadAck(void);
int  TwiReadNAck(void);
uint8_t TwiWrite(uint8_t data);


