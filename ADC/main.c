/*
 * ADC.c
 *
 * Created: 21/12/2017 07:52:15
 * Author : Henrique
 */ 

#include <avr/io.h>
#include "USART/serial.h"



void initADC(void)			
{					
			ADMUX  = (1<<REFS0);	
			ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);		// obs nunca separar o Oring
			ADCSRA = ADCSRA | (1 << ADEN);
						// ADC Enable and prescaler of 128
			// 16000000/128 = 125000		
		
}
uint16_t CanalLeitura(uint8_t canal)
{
	/*ADMUX é o registrador sendo necessário colocar bitwise (&) para eliminar os 4 primeiros bits do ADC
	e deixar o setup anterior do REFS0 para leitura com base com o avcc -> bits 0b0100|0--- 3 bits em
	decimal de 0 a 7 setar a porta para que o ADC realize a leitura*/
	ADMUX = ((ADMUX & 0xF8) | canal);
	// iniciar a conversão do ADC -> analog to digital converter
	ADCSRA |= (1 << ADSC); 
	// aguardar até o ADCSRA concluir a leitura se for falso cai fora do loop
	while(ADCSRA & (1<<ADSC));
	return ADC;					// retorna o valor
}
int main(void)
{
	//int nClock = CLOCK/16/BAUD - 1;		// calculo do clock
	//UsartInitTransmit(nClock);			// para iniciar a transmissão
	uint16_t adcValue;
	uint8_t  ledValue;
	// iniciar a função initADC0	
	DDRD = 0xff;			// todos da porta D como saída		
	// iniciar o ADC
	initADC();	
    while (1) 
    {
		// selecionar a porta de entrada analogica
		adcValue = CanalLeitura(0);
		ledValue = (adcValue >> 7);				// pega apenas tres bits devido a ser 8 leds, cria um filtro de leitura analogica
		PORTD = 0;
		for(int i = 0; i <= ledValue ; i++)
		{
			PORTD |= (1 << i);
		}
		_delay_ms(1);
	}
	return 0;
}

