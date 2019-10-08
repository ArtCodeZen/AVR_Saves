/*
 * EEPROM_Read_Write.c
 *
 * Created: 24/01/2018 20:50:18
 * Author : Henrique
 */ 
#define F_CPU 16000000l
#include <avr/io.h>
#include "EEPROM.h"
#include<util/delay.h>
int main(void)
{
	EEPROM_write(0, 255);		// valores podem serem escritos de 0 a 255 ou 256 
	DDRD = 0xff;
    /* Replace with your application code */
    while (1) 				// main
    {
		if(EEPROM_read(0) == 255)
		{
			PORTD = 0xff;
			_delay_ms(400);
			PORTD = 0x00;
			_delay_ms(400);
		}
		
		
    }
}


