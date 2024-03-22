/*
 * DASHBOARD_System_Clock_Prog.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Sigma
 */

#include "SL_Interface.h"
#include "DASHBOARD_System_Clock_Interface.h"
#include "APP_LCD_INTERFACE.h"

u8 DASHBOARD_Clock_Seconds = SECS_INITIAL_TIME;
u8 DASHBOARD_Clock_Minutes = MINS_INITIAL_TIME;
u8 DASHBOARD_Clock_Hours   = HOURS_INITIAL_TIME;
u32 DASHBOARD_m_Counter=0;
u32 DASHBOARD_Km_Counter = 0; 
u8 Warning_screen_flag = 0;  
u8 Load_variables_time = 0; 
void DASHBOARD_Update_System_Clock(void)
{
	/*static so that the counter don't get cleared by the call*/
	/*increment every time we get into the clock update function*/
	DASHBOARD_Clock_Seconds++;
	if(60 == DASHBOARD_Clock_Seconds)
	{/*after 60 seconds increment minutes counter and clear the seconds*/
		DASHBOARD_Clock_Seconds = 0;
		DASHBOARD_Clock_Minutes++;
	}
	if(60 == DASHBOARD_Clock_Minutes)
	{/*after 60 minutes increment Hours counter and clear the minutes*/
		DASHBOARD_Clock_Minutes = 0;
		DASHBOARD_Clock_Hours++;
	}
	if(24 == DASHBOARD_Clock_Hours)
	{/*after 24 Hours clear all */
		DASHBOARD_Clock_Hours = 0;
		DASHBOARD_Clock_Minutes =0;
		DASHBOARD_Clock_Seconds =0;
	} 
	if (*LCD_PTR == LCD_SCREEN4){ 
		if (Warning_screen_flag == 0){
		APP_Void_LcdUpdateTime(); 
		}		
	}
}
/*******************************************************************
 *
 *
 *
 *
 *
 * ******************************************************************/

void ADAS_SYSTEM_Timer_Handler(void)
{
	DASHBOARD_Update_System_Clock();
	DASHBOARD_Update_Km();/*update the km counter every sec*/
	
	if((SL_STATUS_FLAG == SL_BUTTON_STATUS_ON) && (current_speed > speed_limit))
	{
		H_relay_Tog();
	}
	else if ((SL_STATUS_FLAG == SL_BUTTON_STATUS_OFF) || (current_speed < speed_limit)) {
		H_relay_OFF();
	}
	Inactive_counter++;
	if((Inactive_counter == MAX_INACTIVE_TIME) && (*GEARS_PTR == 'D')){
		/*Warning screen*/
		APP_Void_LcdScreenWarning(); 
		Warning_screen_flag = 1; 
	} 
	/*******************************	SAVE DISTANCE AND TIME TO EPPROM	***************/			
	if ((Load_variables_time % LOAD_VARIABLES_TIME) == 0){
		APP_Void_SaveDistanceToEEPROM();
		APP_Void_SaveClockToEEPROM();
	}
	Load_variables_time++; 
}
/*************************************************************/



void DASHBOARD_Update_Km(void)
{
		/*increment the km counter every sec*/
		DASHBOARD_m_Counter += (u32)((current_speed*5)/18);
		if(DASHBOARD_m_Counter>=1000){
			DASHBOARD_Km_Counter++;
			DASHBOARD_m_Counter-=1000;
		}
}
