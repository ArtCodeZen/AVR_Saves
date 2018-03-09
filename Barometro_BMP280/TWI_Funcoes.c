/*
 * TWI_Funcoes.c
 *
 * Created: 17/01/2018 14:35:23
 *  Author: Henrique
 */ 
#include "TWI_Header.h"
int nCounter = 0;
// função para iniciar o SCL ou o clock de oscilação
void initTWI(void)
{
	
	
	// para calcular o Two Wire Bit Rate, usar a seguinte formula:
	// SCL frequency = CPU Clock frequency / 16 + 2*(TWBR) * PrescalerValue
	//TWSR = 0; // sem prescaler
	TWBR = 72;		// para setar a velocidade de transferência	
	// habilitar o TWI
	TWCR |= (1 << TWEN); 
}

// função para o TWI aguardar a sua transferência de dados
uint8_t TwiAguardar(void)
{
	
	while(!(TWCR & (1 << TWINT))){		
		nCounter++;
		if(nCounter > AGUARDO_TWI)
		{
			nCounter = 0;			// zerar o contador
			return 0;				// retorno 0 - indica erro de envio de dados			
		}		
	}
	nCounter = 0;
	return 1;
}
// começar a transferência de dados
uint8_t TwiStart(uint8_t nEndereco) {	
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);		
	if(!TwiAguardar())					// deu erro de aguardo?
	{ // erro
		SerialPrintString("Erro Start!\n");
		return 0;
	}
	// acessar o registrador com o endereço x em modo de escrita
	TwiWrite(nEndereco);
	return 1;
	
}
void TwiStop(void) 
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
int TwiReadAck(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	if(!TwiAguardar())					// deu erro de aguardo?
	{ // erro
		SerialPrintString("Erro TwiReadAck!\n");
		return 0;
	}
	return (TWDR);
}
int TwiReadNAck(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	if(!TwiAguardar())					// deu erro de aguardo?
	{ // erro
		SerialPrintString("Erro TwiReadNAck!\n");
		return 0;
	}
	return (TWDR);
}
uint8_t TwiWrite(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN); /* iniciar e habilitar */
	if(!TwiAguardar())					// deu erro de aguardo?
	{ // erro
		SerialPrintString("Erro TwiWrite!\n");
		return 0;
	}
	return 1;
}
