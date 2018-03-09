/*
 * BMP280.c
 *
 * Created: 30/01/2018 20:02:18
 *  Author: Henrique
 */ 
#include "BMP280.h"
#include "TWI_Header.h"
#include "Registers_BMP280.h"
// função para iniciar o barômetro
// Parâmetros:
//				Entrada: void
//				Retorno: void
void initBMP280(void)
{
	_delay_ms(100);			// aguardar 100 ms
	TwiStart(ADDRESS_SLAVE);
	
}
