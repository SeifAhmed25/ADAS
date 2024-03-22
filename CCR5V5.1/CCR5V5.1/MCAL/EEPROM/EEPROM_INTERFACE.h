/*
 * EEPROM_INTERFACE.h
 *
 * Created: 3/20/2024 2:05:26 PM
 *  Author: seif
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
#include "BITMATH.h"
#include "STD.h"

void M_EEPROM_Void_WriteByte(u16,u8); 
u8 M_EEPROM_Void_ReadByte(u16 addres);

#endif /* EEPROM_INTERFACE_H_ */