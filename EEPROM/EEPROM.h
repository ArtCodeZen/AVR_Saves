/*
 * EEPROM.h
 *
 * Created: 24/01/2018 21:04:16
 *  Author: Henrique
 */ 

#include <avr/io.h>
// prot�tipos do EEPROM
void EEPROM_write(unsigned int uiAddress, unsigned int ucData);
unsigned int EEPROM_read(unsigned int uiAddress);