/*
 * main.c
 *
 * Created: 3/18/2024 11:38:44 AM
 *  Author: seif
 */ 
/*
 * main.c
 *
 * Created: 3/16/2024 10:14:59 PM
 *  Author: seif
 */ 
/********************************************************************************************************************************************
 *																																			*
 *																HEADER FILES INCLUSION														*
 *																																			*
 ********************************************************************************************************************************************/
#define F_CPU 16000000UL
#include "util/delay.h"
#include "APP_LCD_INTERFACE.h"
#include "CSS_INTERFACE.h"
#include "LCD_Interface.h"
#include "Keypad_Interface.h"
#include "SL_Interface.h"
#include "Timer_Interface.h"
#include "Relay_Interface.h" 
#include "DASHBOARD_System_Clock_Interface.h"
#include "DRIV_MONITORING_INTERFACE.h"
#include "APP_SAVE_TO_EEPROM_INTERFACE.h"
// u8 pressed_button = 0;   
int main(void)
{	
	/*****************************		INITIATE SYSTEM		*************/
	system_CCS_init(); 
	H_Lcd_Void_LCDClear(); 
	/*****************************		START ENGINE	*****************/
	H_Lcd_Void_LCDWriteString((u8*)"PLEASE START ENGINE");
	while (H_KeyPad_U8_KeyPadRead() != 'B'){
						/*WAIT UNTIL THE START ENGINE BUTTON IS PRESSED*/
	} 
	/****************************	READ DISTANCE AND CLOCK FROM EEPROM	*****/
	APP_Void_ReadDistanceFromEEPROM();
	APP_Void_ReadClockFromEEPROM();
	/**************************** SET EXTERNAL INTERRUPT AND TIMER0 CALL BACK FUNCTION	**/
	M_EXTINT_Void_SetCallBack(INT0_CHANNEL,&APP_Void_UpdateGearState); 
	M_Timer_Void_SetCallBack(&ADAS_SYSTEM_Timer_Handler);
	/****************************			INIT TIMER0					*****/
	M_Timer_Void_TimerInit();
	M_Timer_Void_TimerSetTime(TICK_TIME_1SEC);
	M_Timer_Void_TimerStart(TIMER0_CHANNEL);
	/****************************	DISPLAY FIRST SCREEN AS DEFAULT SCREEN	*/
	APP_Void_LcdScreenDisplay();
	u8 key_pressed;
	while (1)
	{	
	/*************************		GET THE CHANGE IN CURRENT SPEED, IF GREATER THAN 5KM THEN UPDATE IT			**********/	
		if (((current_speed-gas_serviceFun()) >= SPEED_CHANGE) || ((gas_serviceFun()-current_speed) >= SPEED_CHANGE)){
			current_speed = gas_serviceFun(); 
			/*UPDATE CRUISR CONTROL FLAG*/
			CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_OFF;
			/************************		If WE ARE IN A WARNING STATE THEN EXIT THE WARNING STATE			**********/
			if (Warning_screen_flag == 1){
				Inactive_counter = 0;
				Warning_screen_flag = 0;
				APP_Void_LcdScreen2(speed_limit,current_speed);
			}
	/*******************	CHECK IF WE ARE IN THE FIRST SCREEN THEN WE UPDATE THE CRUISE STATE ON DISPLAY		*********/
			else if ((*LCD_PTR == LCD_SCREEN1) && (Warning_screen_flag == 0)){
				APP_Void_UpdateLCDCruiseState();
			}
	/******************		CHECK IF WE ARE IN THE SECOND SCREEN THEN WE UPDATE THE CURRENT SPEED ON DISPLAY	**********/ 
			else if (*LCD_PTR == LCD_SCREEN2 && (Warning_screen_flag == 0)){
				APP_Void_UpdateCurrent_Speed();
			}
		}
/***********************************************	GET THE KEYPAD PRESSED BUTTON	*********************************/		 
	key_pressed = H_KeyPad_U8_KeyPadRead(); 
	switch (key_pressed){ 
/**************************************		BRAKE ASSIST BUTTON		************************/
		case BRAKE_ASSIST_KEYPAD_PRESSED : 
			APP_Void_UpdateBrakeAssistState(); 
			if (*LCD_PTR == LCD_SCREEN1 && (Warning_screen_flag == 0)){
				APP_Void_UpdateLCDBrakeAssistState(); 
			}
			else if (Warning_screen_flag == 1){
				APP_Void_LcdScreen1();
			}
			Inactive_counter = 0;
			Warning_screen_flag = 0; 
			break;
/*************************************		BRAKE BUTTON PRESSED	*************************/
		case BRAKE_KEYPAD_PRESSED : 
			brake_serviceFun();
			if (Warning_screen_flag == 1){
				APP_Void_LcdScreen1();
			}
			Inactive_counter = 0;
			Warning_screen_flag = 0;
			break; 
/*************************************		CRUISE BUTTON PRESSED	*************************/
 		case CRUISE_KEYPAD_PRESSED :
			APP_Void_UpdateCruiseState();
			if (*LCD_PTR == LCD_SCREEN1 && (Warning_screen_flag == 0)){
				APP_Void_UpdateLCDCruiseState();
			}
			else if (Warning_screen_flag == 1){
				APP_Void_LcdScreen1();
			}
			Inactive_counter = 0;
			Warning_screen_flag = 0;
			break; 
/*************************************		SCROLL THROUGH LCD SCREENS	**********************/
/*************************************				LEFT				**********************/
		case LCD_LEFT_SCROLL_KEYPAD_PRESSED : 
			APP_Void_UpdateLcdScreen(left);
			Inactive_counter = 0;
			Warning_screen_flag = 0;
			break; 
/*************************************				RIGHT				**********************/			
		case LCD_RIGHT_SCROLL_KEYPAD_PRESSED : 
			APP_Void_UpdateLcdScreen(right);
			Inactive_counter = 0;
			Warning_screen_flag = 0;
			break; 
/*************************************		UPDATE SPEED LIMIT STATE PRESSED	**************/
		case SPEED_LIMIT_STATE_KEYPAD_PRESSED: 
			APP_Void_UpdateSpeedLimitState();
			if (*LCD_PTR == LCD_SCREEN1 && (Warning_screen_flag == 0)){
				APP_Void_UpdateLCDScreen1SpeedLimitState();
			} 
			else if (*LCD_PTR == LCD_SCREEN2 && (Warning_screen_flag == 0)){
				APP_Void_UpdateLCDScreen2SpeedLimitState();
			}
			else if (Warning_screen_flag == 1){
				APP_Void_LcdScreen1();
			}
			Inactive_counter = 0;
			Warning_screen_flag = 0;
 			break;
/*************************************		INCREASE SPEED LIMIT				***************/
		case INCREASE_SPEED_LIMIT_BUTTON:
			if (speed_limit >= MAX_SPEED) {
 				/*DO NOTHING*/
 				}
			else {
 				speed_limit += SPEED_CHANGE; 
				if (*LCD_PTR != LCD_SCREEN2 && (Warning_screen_flag == 0)){
					APP_Void_LcdScreen2 (speed_limit,current_speed);
					*LCD_PTR = LCD_SCREEN2;
				} 
				else if (*LCD_PTR == LCD_SCREEN2 && (Warning_screen_flag == 0)){ 
					APP_Void_UpdateLCDSpeedLimit(speed_limit); 
				}
				else if (Warning_screen_flag == 1){
					APP_Void_LcdScreen2(speed_limit,current_speed);
				}
			 } 
			Inactive_counter = 0;
			Warning_screen_flag = 0;
			break; 
/************************************		DECREASE SPEED LIMIT				***************/
 		case DECREASE_SPEED_LIMIT_BUTTON:
			if (speed_limit <= MIN_SPEED) {
 				/*DO NOTHING*/
 				}
			else { 
				speed_limit -= SPEED_CHANGE;
				if (*LCD_PTR != LCD_SCREEN2 && (Warning_screen_flag == 0)){
					APP_Void_LcdScreen2(speed_limit,current_speed);
					*LCD_PTR = LCD_SCREEN2;
				}
				else if (*LCD_PTR == LCD_SCREEN2 && (Warning_screen_flag == 0)){
					APP_Void_UpdateLCDSpeedLimit(speed_limit);
				} 
				else if (Warning_screen_flag == 1){
					APP_Void_LcdScreen2(speed_limit,current_speed);
				}
 			}
			Inactive_counter = 0;
			Warning_screen_flag = 0;
 			break;
			default:
			break;
		} 
	/*END OF SWITCH CASE*/
	}
}
