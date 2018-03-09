/*
 * serial.h
 *
 * Created: 27/10/2017 20:15:31
 *  Author: Henrique
 */ 
#include "DefinesIncludes.h"
#include <string.h>			// usado pelo lenght
#include <stdlib.h>			// usado pelo itoa integer to alpha
#define CLOCK 16000000
#define BAUD	9600

// definições de protótipos
void tx(unsigned char value);
void UsartInitTransmit(unsigned int nclock);
void SerialPrintInt(int valor);
unsigned char rx(void);
void SerialPrintString(char *ptrAcao);
void SerialPrintHexa(int valor);
