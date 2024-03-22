/*
 * EPPROM.c
 *
 * Created: 3/20/2024 2:04:15 PM
 *  Author: seif
 */ 
#include "EEPROM_INTERFACE.h" 
#include "EEPROM_PRIVATE.h"
void M_EEPROM_Void_WriteByte(u16 address, u8 data){
	while (GET_BIT(EECR,EEWE)){
		/*WAIT UNTIL THE LAST WRITE TO EEPROM TO BE COMPLETED*/
	} 
	/* Set up address and data registers */
	EEARL = address; 
	EEARH = address >> 8; 
	EEDR = data;
	/* SET EEMWE BIT
	 */ 
	SET_BIT (EECR,EEMWE);
	/* SET EEWE BIT
	 */ 
	SET_BIT (EECR,EEWE); 
} 
u8 M_EEPROM_Void_ReadByte(u16 address){
	while (GET_BIT(EECR,EEWE)){
		/*WAIT UNTIL THE LAST WRITE TO EEPROM TO BE COMPLETED*/
	} 
	/* Set up address two registers */
	EEARL = address;
	EEARH = address >> 8;
	/*ENABLE EEPROM ENABLE BIT*/ 
	SET_BIT(EECR,EERE); 
	
	return (EEDR);
}