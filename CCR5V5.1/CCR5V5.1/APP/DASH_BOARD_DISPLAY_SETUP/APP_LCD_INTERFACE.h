/*
 * IncFile1.h
 *
 * Created: 3/16/2024 10:17:59 PM
 *  Author: seif
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_ 

#include "STD.h" 
#include "BitMath.h"
#include "LCD_Interface.h"
#include "APP_LCD_CONFIG.h"
#include "SL_Interface.h" 
#include "CSS_INTERFACE.h"
#include "DRIV_MONITORING_INTERFACE.h"
#include  "DASHBOARD_System_Clock_Interface.h"


extern u8 speed_limit;
extern u8 current_speed;
extern u8* LCD_PTR; 
extern u8 SL_STATUS_FLAG; 
extern u8* GEARS_PTR;
extern u8 CRUISE_STATUS_FLAG ;
void APP_Void_UpdateGearState(void); 
u8* APP_U8_CurrentGearState (void);

void APP_Void_UpdateCruiseState(void);
u8* APP_U8_CurrentCruiseState(void);

void APP_Void_UpdateBrakeAssistState(void);
u8* APP_U8_CurrentBrakeAssistState(void); 

void APP_Void_UpdateSpeedLimitState(void);
u8* APP_U8_CurrentSpeedLimitState(void);

u8* APP_U8_CurrentDriverMonitoringState (void);
void APP_Void_LcdScreen1 (void); 
void APP_Void_LcdScreen2(s32 speed_limit , s32 current_speed); 
void APP_Void_LcdScreen3(void);

void APP_Void_UpdateLcdScreen(u8); 
void APP_Void_LcdScreenDisplay(void);

void APP_Void_UpdateCurrent_Speed(void);  
void APP_Void_UpdateLCDCruiseState(void);
void APP_Void_UpdateLCDBrakeAssistState(void);
void APP_Void_UpdateLCDScreen1SpeedLimitState(void);
void APP_Void_UpdateLCDScreen2SpeedLimitState(void); 
void APP_Void_UpdateLCDSpeedLimit(s32 speed_limit); 

void APP_Void_LcdUpdateTime(void);
void APP_Void_LcdScreenWarning(void);

void APP_Void_UpdateDmState(void);

#endif /* INCFILE1_H_ */
