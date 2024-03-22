/*
 * DASHBOARD_System.Clock_Interface.h
 *
 *  Created on: Mar 17, 2024
 *      Author: Sigma
 */

#ifndef APP_DASHBOARD_SYSTEM_CLOCK_DASHBOARD_SYSTEM_CLOCK_INTERFACE_H_
#define APP_DASHBOARD_SYSTEM_CLOCK_DASHBOARD_SYSTEM_CLOCK_INTERFACE_H_

#include "DASHBOARD_System_Clock_Config.h"
#include "APP_LCD_INTERFACE.h"
#include "Timer_Interface.h"
#include "APP_SAVE_TO_EEPROM_INTERFACE.h"

extern u8 DASHBOARD_Clock_Seconds;
extern u8 DASHBOARD_Clock_Minutes;
extern u8 DASHBOARD_Clock_Hours;
extern u8 Warning_screen_flag;

extern u32 DASHBOARD_Km_Counter;
extern u32 DASHBOARD_m_Counter;
void DASHBOARD_Update_System_Clock(void); 

void ADAS_SYSTEM_Timer_Handler(void);

void DASHBOARD_Update_Km(void);

#endif /* APP_DASHBOARD_SYSTEM_CLOCK_DASHBOARD_SYSTEM_CLOCK_INTERFACE_H_ */
