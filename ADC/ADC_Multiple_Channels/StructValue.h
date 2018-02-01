/*
 * StructValue.h
 *
 * Created: 21/12/2017 20:00:01
 *  Author: Henrique
 */ 
#define QTDE_CANAIS_ADC		2		

typedef struct value
{
	uint8_t nCanal;			// número do canal
	uint16_t nValor;		// Valor que o canal atual possui
}VALOR;