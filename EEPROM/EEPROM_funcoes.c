/*
 * EEPROM_funcoes.c
 *
 * Created: 24/01/2018 20:51:32
 *  Author: Henrique
 */ 

// fun��o para escrever o valor na mem�ria EEPROM
// Par�metros:
//				Entrada:
//						unsigned int uiAdress - inteiro sem sinal para conter o endere�o de escrita
//						unsigned char ucdata  - para conter o valor para ser escrito no eeprom
//				Retorno: void - n�o retorna nada!
#include "EEPROM.h"
void EEPROM_write(unsigned int uiAddress, unsigned int ucData)
{
	// aguarde completar a escrita anterior
	while(EECR & (1<<EEPE));
	// setar o endere�o e o registrador de valor
	EEAR = uiAddress;
	EEDR = ucData;
	// escreva logicamente 1 para o registro de controle
	EECR |= (1<<EEMPE);
	// iniciar como modo escrita master
	EECR |= (1<<EEPE);
}

// fun��o para ler o valor contido no endere�o x da EEPROM
// Par�metros:
//			Entrada: 
//						uint16_t uiAddress - inteiro sem sinal para conter o endere�o como � 1K o atmega 328p = 1024 bytes 
//			Retorno:	
//						uint8_t  - retorna o valor da leitura do EEPROM
uint8_t EEPROM_read(unsigned uint16_t uiAddress)
{
	// esperar completar a escrita anterior
	while(EECR & (1<<EEPE));
	// configurar o registrador de endere�o
	EEAR = uiAddress;
	// iniciar o EEPROM em modo de leitura
	EECR |= (1<<EERE);
	// Retornar o valor lido dentro do registrador
	return EEDR;
}