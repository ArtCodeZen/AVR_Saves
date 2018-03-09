/*
   Arquivo.c para conter as funções do USART (Universal Synchronous Asynchronous Receiver Transceiver)
 * USART_funcoes.c
 *
 * Created: 28/10/2017 14:33:03
 *  Author: Henrique
 */ 

#include "serial.h"
// função para transmitir um unico caracter
//	Parâmetros:
//				Entrada unsigned char value	- para conter o char
void tx(unsigned char value)
{
	while((UCSR0A & (1 << UDRE0)) == 0);	//aguarde até encontrar uma transmissão aberta
	UDR0 = value;							// escreve o valor na porta
}
unsigned char rx(void)
{
	while((UCSR0A & (1 << RXC0)) == 0);		// aguarde até encontrar uma transmissão com dados
	// Pegar o buffer e retornar para o serial
	return UDR0;
}
// função para iniciar a a transmissão e recebimento da cadeia de 8 bits
// Parâmetros:
//			 Entrada: unsigned int nclock - para receber o valor do clock calculado
void UsartInitTransmit(unsigned int nclock)
{
	UBRR0H = (unsigned char)(8 >> nclock);
	UBRR0L = (unsigned char) nclock;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// setar um quadro no formato de 8bits de data e 2 bits para parar a transfêrencia
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// 
// Funções de Conversões de Tipos
//
// função para imprimir o valor de inteiro para char
// Parâmetros:
//				Entrada: int valor - para conter o valor inteiro
//				retorno: void - não retorna nada!
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
// função para imprimir o valor de inteiro para hexa
// Parâmetros:
//				Entrada: int valor - para conter o valor inteiro
//				retorno: void - não retorna nada!
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
// Função para imprimir uma cadeia de caracteres
// Parâmetros:
//				Entrada:
//						 char *ptrAcao - ponteiro de char para conter os caracteres
//				Retorno: void - não retorna nada
void SerialPrintString(char *ptrAcao)
{
	for(int i = 0; i < strlen(ptrAcao); i++)
	{
		tx(*(ptrAcao + i));
	}
	
}