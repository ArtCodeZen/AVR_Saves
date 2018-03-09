/*
 * Barometro_BMP280.c
 *
 * Created: 30/01/2018 19:56:22
 * Author : Henrique
 */ 

#include <avr/io.h>
#include "TWI_Header.h"

int main(void)
{
    // iniciar o serial
	int nClock = CLOCK/16/BAUD - 1;		// calculo do clock
	UsartInitTransmit(nClock);			// para iniciar a transmissão
    initTWI();
	// para iniciar o barometro
	TwiStart(0xEC);
	TwiWrite(0xF4);
	TwiWrite(0x3F);
	TwiStop();
	while (1) 
    {
		
		TwiStart(0xEC);
		TwiWrite(0xF7);
		TwiStop();
		TwiStart(0xEC + 1);		// read mode
		SerialPrintInt((TwiReadAck() << 8) | TwiReadNAck());
		TwiStop();
		_delay_ms(300);
    }
}

