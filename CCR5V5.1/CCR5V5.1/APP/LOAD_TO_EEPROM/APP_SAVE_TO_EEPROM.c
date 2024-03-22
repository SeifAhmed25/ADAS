/*
 * APP_SAVE_TO_EEPROM.c
 *
 * Created: 3/20/2024 4:06:56 PM
 *  Author: seif
 */ 
#include "APP_SAVE_TO_EEPROM_INTERFACE.h"

void APP_Void_SaveDistanceToEEPROM(){
	u32 km = DASHBOARD_Km_Counter;
	u16 m = DASHBOARD_m_Counter;
	u8 i;
	/* Write 4 bytes for km_counter */
	for (i = 0; i < 4; i++) {
		M_EEPROM_Void_WriteByte(i, (u8)km);
		km >>= 8;
	}
	/* Write 2 bytes for m_counter */
	for (i = 0; i < 2; i++) {
		M_EEPROM_Void_WriteByte(i + 4, (u8)m);
		m >>= 8;
	}
}
void APP_Void_ReadDistanceFromEEPROM(){
	u8 i;
	u8 km;
	u8 m;
	/* Read first 4 bytes for km_counter */
	DASHBOARD_Km_Counter = 0; 
	for (i = 0; i < 4; i++) {
		km = M_EEPROM_Void_ReadByte(i);
		DASHBOARD_Km_Counter |= ((u32)km << (i * 8));
	}
	/* Read next 2 bytes for m_counter */
	DASHBOARD_m_Counter = 0; 
	for (i = 0; i < 2; i++) {
		m = M_EEPROM_Void_ReadByte(i + 4);
		DASHBOARD_m_Counter |= ((u16)m << (i * 8));
	}
} 
void APP_Void_SaveClockToEEPROM(){
	M_EEPROM_Void_WriteByte(6,DASHBOARD_Clock_Hours); 
	M_EEPROM_Void_WriteByte(7,DASHBOARD_Clock_Minutes);
	M_EEPROM_Void_WriteByte(8,DASHBOARD_Clock_Seconds);
}
void APP_Void_ReadClockFromEEPROM(){
	DASHBOARD_Clock_Hours = M_EEPROM_Void_ReadByte(6); 
	DASHBOARD_Clock_Minutes = M_EEPROM_Void_ReadByte(7);
	DASHBOARD_Clock_Seconds = M_EEPROM_Void_ReadByte(8);
}