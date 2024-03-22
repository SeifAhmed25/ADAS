/*
 * APP_SAVE_TO_EEPROM.h
 *
 * Created: 3/20/2024 4:07:25 PM
 *  Author: seif
 */ 


#ifndef APP_SAVE_TO_EEPROM_H_
#define APP_SAVE_TO_EEPROM_H_
#include "EEPROM_INTERFACE.h" 
#include "DASHBOARD_System_Clock_Interface.h"

void APP_Void_SaveDistanceToEEPROM(void);
void APP_Void_ReadDistanceFromEEPROM(void);
void APP_Void_SaveClockToEEPROM(void); 
void APP_Void_ReadClockFromEEPROM(void);


#endif /* APP_SAVE_TO_EEPROM_H_ */