/*
   Arquivo.c para conter as fun��es do USART (Universal Synchronous Asynchronous Receiver Transceiver)
 * USART_funcoes.c
 *
 * Created: 28/10/2017 14:33:03
 *  Author: Henrique
 */ 

#include "serial.h"
// fun��o para transmitir um unico caracter
//	Par�metros:
//				Entrada unsigned char value	- para conter o char
void tx(unsigned char value)
{
	while((UCSR0A & (1 << UDRE0)) == 0);	//aguarde at� encontrar uma transmiss�o aberta
	UDR0 = value;							// escreve o valor na porta
}
unsigned char rx(void)
{
	while((UCSR0A & (1 << RXC0)) == 0);		// aguarde at� encontrar uma transmiss�o com dados
	// Pegar o buffer e retornar para o serial
	return UDR0;
}
// fun��o para iniciar a a transmiss�o e recebimento da cadeia de 8 bits
// Par�metros:
//			 Entrada: unsigned int nclock - para receber o valor do clock calculado
void UsartInitTransmit(unsigned int nclock)
{
	UBRR0H = (unsigned char)(8 >> nclock);
	UBRR0L = (unsigned char) nclock;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// setar um quadro no formato de 8bits de data e 2 bits para parar a transf�rencia
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// 
// Fun��es de Convers�es de Tipos
//
// fun��o para imprimir o valor de inteiro para char
// Par�metros:
//				Entrada: int valor - para conter o valor inteiro
//				retorno: void - n�o retorna nada!
void SerialPrintInt(int valor)
{
	char vetChar[10];
	itoa(valor, vetChar, 10);			// tranformar no tipo decimal
	for(int i = 0; i < strlen(vetChar); i++)
	{
		tx(vetChar[i]);					// percorrer o vetor com os caracteres
	}
	// pular de linha, terminou a transferencia da string
	tx('\n');	
}
// fun��o para imprimir o valor de inteiro para hexa
// Par�metros:
//				Entrada: int valor - para conter o valor inteiro
//				retorno: void - n�o retorna nada!
void SerialPrintHexa(int valor)
{
	char vetChar[10];
	itoa(valor, vetChar, 16);			// tranformar no tipo hexadecimal
	for(int i = 0; i < strlen(vetChar); i++)
	{
		tx(vetChar[i]);					// percorrer o vetor com os caracteres
	}
	// pular de linha, terminou a transferencia da string
	tx('\n');
}
// Fun��o para imprimir uma cadeia de caracteres
// Par�metros:
//				Entrada:
//						 char *ptrAcao - ponteiro de char para conter os caracteres
//				Retorno: void - n�o retorna nada
void SerialPrintString(char *ptrAcao)
{
	for(int i = 0; i < strlen(ptrAcao); i++)
	{
		tx(*(ptrAcao + i));
	}
	
}