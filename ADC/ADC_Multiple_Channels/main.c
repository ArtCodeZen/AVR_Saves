/*
 * ADC_Multiple_Channels.c
 *
 * Created: 21/12/2017 17:32:56
 * Author : Henrique
 */ 

#include <avr/io.h>
#include "USART/serial.h"
#include "StructValue.h"
#include <stdlib.h>
#include <string.h>

void initADC(void)
{
	ADMUX |= (1 << REFS0);											// usar base de referencia avcc
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// prescaler /16
	ADCSRA |= (1 << ADEN);											// habilitar ADC
}
void LeituraCanalADC(uint8_t ch, VALOR *ptrStructValor)
{
	
	ADMUX = (ADMUX & 0xF8) | ch;							// selecionar o canal
	ADCSRA |= (1 << ADSC);									// iniciar conversão de valor
	// aguardar até o ADCSRA concluir a leitura se for falso cai fora do loop
	while(ADCSRA & (1<<ADSC));
	ptrStructValor->nCanal = ch;			// para conter o valor do canal
	ptrStructValor->nValor = ADC;			// para conter o valor da leitura
}
void SerialPrintInt(int valor)
{
	char vetChar[10];
	itoa(valor, vetChar, 10);			// tranformar no tipo decimal
	for(uint8_t i = 0; i < strlen(vetChar); i++)
	{
		tx(vetChar[i]);					// percorrer o vetor com os caracteres
	}
	// pular de linha, terminou a transferencia da string
	
	return;
}
void SerialPrintString(char *ptrAcao)
{
	for(int i = 0; i < strlen(ptrAcao); i++)
	{
		tx(*(ptrAcao + i));
	}
	
}
int main(void)
{

    int nClock = CLOCK/16/(BAUD) - 1;		// calculo do clock
    UsartInitTransmit(nClock);			// para iniciar a transmissão serial
	initADC();
	VALOR vetStrValor[QTDE_CANAIS_ADC];				// para conter um vetor de estruct com os canais
	uint8_t vetCanais[QTDE_CANAIS_ADC] = {0,1};
		DDRD = 0xfc;
	while (1) 
    {
		// fazer a leitura dos canais e inserir dentro da struct
		for(int i = 0; i < QTDE_CANAIS_ADC; i++)
		{
			LeituraCanalADC(vetCanais[i], &vetStrValor[i]);			// fazer a leitura do canal e depois inserir dentro da struct		
		}
		for(int i = 0; i < QTDE_CANAIS_ADC; i++)
		{
			
			SerialPrintString("Canal: ");
			SerialPrintInt(vetStrValor[i].nCanal);
			SerialPrintString("--->>");		
			SerialPrintString("Valor: ");
			SerialPrintInt(vetStrValor[i].nValor >> 7);
			SerialPrintString("\t");
			
			_delay_ms(30);
		}
		SerialPrintString("\n");
		PORTD = 0;
		for(int j = 0; j <= vetStrValor[1].nValor >> 7; j++)
		{
			PORTD |= (1 << j);
		}
			

			
    }
}

