/*
 * EEPROM_funcoes.c
 *
 * Created: 24/01/2018 20:51:32
 *  Author: Henrique
 */ 

// função para escrever o valor na memória EEPROM
// Parâmetros:
//				Entrada:
//						unsigned int uiAdress - inteiro sem sinal para conter o endereço de escrita
//						unsigned char ucdata  - para conter o valor para ser escrito no eeprom
//				Retorno: void - não retorna nada!
#include "EEPROM.h"
void EEPROM_write(unsigned int uiAddress, unsigned int ucData)
{
	// aguarde completar a escrita anterior
	while(EECR & (1<<EEPE));
	// setar o endereço e o registrador de valor
	EEAR = uiAddress;
	EEDR = ucData;
	// escreva logicamente 1 para o registro de controle
	EECR |= (1<<EEMPE);
	// iniciar como modo escrita master
	EECR |= (1<<EEPE);
}

// função para ler o valor contido no endereço x da EEPROM
// Parâmetros:
//			Entrada: 
//						uint16_t uiAddress - inteiro sem sinal para conter o endereço como é 1K o atmega 328p = 1024 bytes 
//			Retorno:	
//						uint8_t  - retorna o valor da leitura do EEPROM
uint8_t EEPROM_read(unsigned uint16_t uiAddress)
{
	// esperar completar a escrita anterior
	while(EECR & (1<<EEPE));
	// configurar o registrador de endereço
	EEAR = uiAddress;
	// iniciar o EEPROM em modo de leitura
	EECR |= (1<<EERE);
	// Retornar o valor lido dentro do registrador
	return EEDR;
}