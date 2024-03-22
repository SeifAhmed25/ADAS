/*
 * CCR4.c
 *
 * Created: 3/16/2024 1:11:41 PM
 * Author : seif
 */ 

#include "APP_LCD_INTERFACE.h"
u8 speed_limit   = INITIAL_SPEED_LIMIT_VALUE;
u8 current_speed = INITAL_CURRENT_SPEED_VALUE;

/*********************************************** STATUS DISPLAY ****************************************/
/*********************************************** 	GEARS		***************************************/
u8 GEAR_STATUS_DISPLAY[][20] = {"RND STATUS: N", "RND STATUS: D", "RND STATUS: R"};
u8 GEAR_STATES [] = {'N','R','D'}; 
u8* GEARS_PTR = GEAR_STATES;
/**********************************************		  CRUISE		************************************/
u8 CRUISE_STATUS_DISPLAY [][20] = {"CR STATUS: OFF","CR STATUS: ON "};
u8 CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_OFF;
/**********************************************		BRAKE ASSIST	************************************/
u8 BRAKE_ASSIST_STATUS_DISPLAY [][20] = {"BA STATUS:OFF","BA STATUS:ON "};
u8 BA_STATUS_FLAG = BA_BUTTON_STATUS_OFF;
/******************************************			SPEED LIMIT		 ***********************************/
u8 SPEED_LIMIT_STATUS_DISPLAY [][20] = {"SL ST:OFF ", "SL ST:ON "};
u8 SPEED_LIM_DISPLAY[] =  "SPEED LIM: ";
u8 CURRENT_SPEED_DISPLAY[] = "CURR SPD: ";
/**********************************************		DM SYSTEM		  ***********************************/
u8 DRIVER_MONITORING_STATUS_DISPLAY [][20] = {"DM ST: OFF","DM ST: ON "};
/**********************************************		SCREEN NUMBER	  ***********************************/
u8 SCREEN_NUMBER_DISPLAY [][20] = {"1/4", "2/4", "3/4", "4/4"};
/**********************************************	FUEL, OIL, MOTOR TEMP, UNIT *****************************/
u8 FUEL_LEVEL_DISPLAY[] = "FUEL LEVEL: ";
u8 OIL_LEVEL_DISPLAY[] = "OIL LEVEL: "; 
u8 MOTOR_TEMP_DISPLAY[]  = "MOTOR TEMP: "; 
u8 KM_H[] = "km/h  ";
/**********************************************    TRACK THE LCD SCREEN  ********************************/ 
u8 LCD_DISPLAYS[] = {LCD_SCREEN1, LCD_SCREEN2, LCD_SCREEN3, LCD_SCREEN4};
u8* LCD_PTR = LCD_DISPLAYS;
/********************************************** 	DATE DISPLAY			******************************/
u8 DATE_LCD_DISPLAY [20] = "DATE: MON - 18/03";
/**********************************************		TIME DISPLAY			******************************/
u8 TIME_LCD_DISPLAY [20] = "TIME: " ;
/**********************************************		  KM COUNTER			******************************/
u8 KM_COUNTER_LCD_DISPLAY [20] = "KM: ";
/********************************************** SCREEN1, SCREEN2, SCREEN3   ******************************/
/********************************************** FUNCTIONS IMPLEMENTATION ********************************/
/**********************************************   CHECK AND UPDATE GEAR STATES	 ********************************/
void APP_Void_UpdateGearState(void){ 
	if (brake_flag == BRAKE_ON){
	GEARBOX_PRESSED_NOTIFICATION_BUZZER();
		if (*GEARS_PTR == 'N'){
			CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_OFF;
			SL_STATUS_FLAG = SL_BUTTON_STATUS_OFF;
			Driv_monitoring_status_flag = DRIV_MONITORING_OFF;
			GEARS_PTR++; 
		} 
		else if (*GEARS_PTR == 'R'){
			Driv_monitoring_status_flag = DRIV_MONITORING_ON;
			if (*LCD_PTR == LCD_SCREEN1){
				H_Lcd_Void_LCDGoTo(3,10);
				H_Lcd_Void_LCDWriteString(APP_U8_CurrentDriverMonitoringState());
			}
			GEARS_PTR++;
		}
		else if (*GEARS_PTR == 'D'){
			CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_OFF;
			SL_STATUS_FLAG = SL_BUTTON_STATUS_OFF;
			Driv_monitoring_status_flag = DRIV_MONITORING_OFF; 
			if (*LCD_PTR == LCD_SCREEN1){
				H_Lcd_Void_LCDGoTo(3,10);
				H_Lcd_Void_LCDWriteString(APP_U8_CurrentDriverMonitoringState());
			}
			GEARS_PTR = GEAR_STATES;
		}
		H_Lcd_Void_LCDGoTo(0,0);
		H_Lcd_Void_LCDWriteString(APP_U8_CurrentGearState());
	}
}
u8* APP_U8_CurrentGearState (void){ 
	u8* ptr = '\0'; 
	if (*GEARS_PTR == 'N'){
		ptr = GEAR_LCD_STATUS_N; 
	}
	else if (*GEARS_PTR == 'R'){
		ptr = GEAR_LCD_STATUS_R;
	}
	else if (*GEARS_PTR == 'D'){
		ptr = GEAR_LCD_STATUS_D; 
	} 
	return ptr;
} 
/**********************************************	  CHECK ON CRUISE STATE	 ********************************/
void APP_Void_UpdateCruiseState(void){
	if ((CRUISE_STATUS_FLAG == CRUISE_BUTTON_STATUS_OFF) && (*GEARS_PTR == 'D')){ 
		CCS_PRESSED_NOTIFICATION_BUZZER();
		CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_ON;
	}
	else if (CRUISE_STATUS_FLAG == CRUISE_BUTTON_STATUS_ON){
		CCS_PRESSED_NOTIFICATION_BUZZER();
		CRUISE_STATUS_FLAG = CRUISE_BUTTON_STATUS_OFF;
	}
}
u8* APP_U8_CurrentCruiseState(void){
	u8* ptr = '\0';
	if (CRUISE_STATUS_FLAG == CRUISE_BUTTON_STATUS_OFF){
		ptr = CRUISE_LCD_STATUS_OFF;
	}
	else if (CRUISE_STATUS_FLAG == CRUISE_BUTTON_STATUS_ON){
		ptr = CRUISE_LCD_STATUS_ON;
	}
	return ptr;
}
/**********************************************  CHECK ON BREAK ASSIST STATE  ****************************/
void APP_Void_UpdateBrakeAssistState(void){
	if (BA_STATUS_FLAG == BA_BUTTON_STATUS_OFF){
		BA_STATUS_FLAG = BA_BUTTON_STATUS_ON;
	}
	else if (BA_STATUS_FLAG == BA_BUTTON_STATUS_ON){
		BA_STATUS_FLAG = BA_BUTTON_STATUS_OFF;
	}
}
u8* APP_U8_CurrentBrakeAssistState(void){
	u8* ptr = '\0';
	if (BA_STATUS_FLAG == BA_BUTTON_STATUS_OFF){
		ptr = BA_LCD_STATUS_OFF;
	}
	else if (BA_STATUS_FLAG == BA_BUTTON_STATUS_ON){
		ptr = BA_LCD_STATUS_ON;
	}
	return ptr;
} 
/**********************************************	 CHECK ON SPEED LIMIT STATE *****************************/
void APP_Void_UpdateSpeedLimitState(void){
	if ((SL_STATUS_FLAG == SL_BUTTON_STATUS_OFF) && (*GEARS_PTR == 'D')){
		SL_STATUS_FLAG = SL_BUTTON_STATUS_ON;
	}
	else if (SL_STATUS_FLAG == SL_BUTTON_STATUS_ON){
		SL_STATUS_FLAG = SL_BUTTON_STATUS_OFF;
	}
}
u8* APP_U8_CurrentSpeedLimitState(void){
	u8* ptr = '\0';
	if (SL_STATUS_FLAG == SL_BUTTON_STATUS_OFF){
		ptr = SL_LCD_STATUS_OFF;
	}
	else if (SL_STATUS_FLAG == SL_BUTTON_STATUS_ON){
		ptr = SL_LCD_STATUS_ON;
	}
	return ptr;
}
/********************************************** CHECK ON DRIVER MON STATE   ******************************/
void APP_Void_UpdateDmState (void){
	if (Driv_monitoring_status_flag == DRIV_MONITORING_OFF){
		Driv_monitoring_status_flag = DRIV_MONITORING_ON;
	}
	else if (Driv_monitoring_status_flag == DRIV_MONITORING_ON){
		Driv_monitoring_status_flag = DRIV_MONITORING_OFF;
	}
}
u8* APP_U8_CurrentDriverMonitoringState (void){
	u8* ptr = '\0';
	if (Driv_monitoring_status_flag == DRIV_MONITORING_OFF){
		ptr = DM_LCD_STATUS_OFF;
	}
	else if (Driv_monitoring_status_flag == DRIV_MONITORING_ON){
		ptr = DM_LCD_STATUS_ON;
	}
	return ptr;
}
void APP_Void_LcdScreen1 (){
	H_Lcd_Void_LCDClear(); 
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentGearState());
	H_Lcd_Void_LCDGoTo(0,17);
	H_Lcd_Void_LCDWriteString(SCREEN_NUMBER_DISPLAY[0]); 
	H_Lcd_Void_LCDGoTo(1,0); 
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentCruiseState()); 
	H_Lcd_Void_LCDGoTo(2,0); 
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentBrakeAssistState());
	H_Lcd_Void_LCDGoTo(3,0); 
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentSpeedLimitState());
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentDriverMonitoringState());
}
void APP_Void_LcdScreen2(s32 speed_limit , s32 current_speed){
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentGearState());
	H_Lcd_Void_LCDGoTo(0,17);
	H_Lcd_Void_LCDWriteString(SCREEN_NUMBER_DISPLAY[1]);
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentSpeedLimitState()); 
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString(SPEED_LIM_DISPLAY); 
	H_Lcd_Void_LCDWriteNumber(speed_limit); 
	H_Lcd_Void_LCDWriteString(KM_H); 
	H_Lcd_Void_LCDGoTo(3,0);
	H_Lcd_Void_LCDWriteString(CURRENT_SPEED_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(current_speed); 
	H_Lcd_Void_LCDWriteString(KM_H);
}
void APP_Void_LcdScreen3(){
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentGearState());
	H_Lcd_Void_LCDGoTo(0,17);
	H_Lcd_Void_LCDWriteString(SCREEN_NUMBER_DISPLAY[2]);
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString(FUEL_LEVEL_DISPLAY); 
	H_Lcd_Void_LCDWriteNumber(54);
	H_Lcd_Void_LCDWriteCharacter('%');
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString(OIL_LEVEL_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(62);
	H_Lcd_Void_LCDWriteCharacter('%');	
	H_Lcd_Void_LCDGoTo(3,0);
	H_Lcd_Void_LCDWriteString(MOTOR_TEMP_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(80);
	H_Lcd_Void_LCDWriteCharacter('C');
}
void APP_Void_LcdScreen4(){
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentGearState());
	H_Lcd_Void_LCDGoTo(0,17);
	H_Lcd_Void_LCDWriteString(SCREEN_NUMBER_DISPLAY[3]);
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString(DATE_LCD_DISPLAY);
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString(TIME_LCD_DISPLAY);
	/***************************************************************************************************************/
	if (DASHBOARD_Clock_Hours < 10){
		H_Lcd_Void_LCDGoTo(2,6);
		H_Lcd_Void_LCDWriteNumber(0);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Hours);
	}
	else {
		H_Lcd_Void_LCDGoTo(2,6);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Hours);
	}
	H_Lcd_Void_LCDWriteCharacter(':');
	if (DASHBOARD_Clock_Minutes < 10){
		H_Lcd_Void_LCDGoTo(2,9);
		H_Lcd_Void_LCDWriteNumber(0);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Minutes);
	}
	else{
		H_Lcd_Void_LCDGoTo(2,9);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Minutes);
	}
	H_Lcd_Void_LCDWriteCharacter(':');
	if (DASHBOARD_Clock_Seconds < 10){
		H_Lcd_Void_LCDGoTo(2,12);
		H_Lcd_Void_LCDWriteNumber(0);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Seconds);
	}
	else{
		H_Lcd_Void_LCDGoTo(2,12);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Seconds);
		H_Lcd_Void_LCDWriteString((u8*)" KM  ");		
	}
	/**********************************************************************************************************************/
	H_Lcd_Void_LCDGoTo(3,0);
	H_Lcd_Void_LCDWriteString(KM_COUNTER_LCD_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(DASHBOARD_Km_Counter);
	H_Lcd_Void_LCDWriteString((u8*)" KM ");
	H_Lcd_Void_LCDWriteNumber(DASHBOARD_m_Counter);
	H_Lcd_Void_LCDWriteString((u8*)" M ");
} 
void APP_Void_LcdScreenDisplay(){
	if (*LCD_PTR == LCD_SCREEN1){
		APP_Void_LcdScreen1();
	}
	else if (*LCD_PTR == LCD_SCREEN2){
		APP_Void_LcdScreen2(speed_limit,current_speed);
	}
	else if (*LCD_PTR == LCD_SCREEN3){
		APP_Void_LcdScreen3();
	}
	else if (*LCD_PTR == LCD_SCREEN4){
		cli();
		APP_Void_LcdScreen4();
		sei();
	}
}
void APP_Void_UpdateLcdScreen (u8 direction){
	switch (direction){
		case right:
			if (*LCD_PTR == LCD_SCREEN1){
				LCD_PTR++; 
			} 
			else if (*LCD_PTR == LCD_SCREEN2){
				LCD_PTR++;
			}
			else if (*LCD_PTR == LCD_SCREEN3)
				LCD_PTR++;
			else if (*LCD_PTR == LCD_SCREEN4)
				LCD_PTR = LCD_DISPLAYS;
				break;
		case left:
			if (*LCD_PTR == LCD_SCREEN1){
				LCD_PTR+=3;
			}
			else if (*LCD_PTR == LCD_SCREEN2){
				LCD_PTR--;
			}
			else if (*LCD_PTR == LCD_SCREEN3)
				LCD_PTR--;
			else if (*LCD_PTR == LCD_SCREEN4)
							LCD_PTR--;
				break; 
	}
	APP_Void_LcdScreenDisplay();
}
void APP_Void_UpdateCurrent_Speed(){
	H_Lcd_Void_LCDGoTo(3,0);
	H_Lcd_Void_LCDWriteString(CURRENT_SPEED_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(current_speed);
	H_Lcd_Void_LCDWriteString(KM_H);
} 
void APP_Void_UpdateLCDCruiseState(){
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentCruiseState());
} 
void APP_Void_UpdateLCDBrakeAssistState(){
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentBrakeAssistState());
} 
void APP_Void_UpdateLCDScreen1SpeedLimitState(){
	H_Lcd_Void_LCDGoTo(3,0);
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentSpeedLimitState());
} 
void APP_Void_UpdateLCDScreen2SpeedLimitState(){
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString(APP_U8_CurrentSpeedLimitState());
} 
void APP_Void_UpdateLCDSpeedLimit(s32 speed_limit){
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString(SPEED_LIM_DISPLAY);
	H_Lcd_Void_LCDWriteNumber(speed_limit);
	H_Lcd_Void_LCDWriteString(KM_H);
}
void APP_Void_LcdUpdateTime(){
		if (DASHBOARD_Clock_Hours < 10){
			H_Lcd_Void_LCDGoTo(2,6);
			H_Lcd_Void_LCDWriteNumber(0);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Hours);
		}
		else {
			H_Lcd_Void_LCDGoTo(2,6);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Hours);
		}
		H_Lcd_Void_LCDWriteCharacter(':');
		if (DASHBOARD_Clock_Minutes < 10){
			H_Lcd_Void_LCDGoTo(2,9);
			H_Lcd_Void_LCDWriteNumber(0);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Minutes);
		}
		else{
			H_Lcd_Void_LCDGoTo(2,9);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Minutes);
		}
		H_Lcd_Void_LCDWriteCharacter(':');
		if (DASHBOARD_Clock_Seconds < 10){
			H_Lcd_Void_LCDGoTo(2,12);
			H_Lcd_Void_LCDWriteNumber(0);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Seconds);
		}
		else{
			H_Lcd_Void_LCDGoTo(2,12);
			H_Lcd_Void_LCDWriteNumber(DASHBOARD_Clock_Seconds);
		}
		H_Lcd_Void_LCDGoTo(3,0);
		H_Lcd_Void_LCDWriteString(KM_COUNTER_LCD_DISPLAY);
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_Km_Counter);
		H_Lcd_Void_LCDWriteString((u8*)" KM ");
		H_Lcd_Void_LCDWriteNumber(DASHBOARD_m_Counter);
		H_Lcd_Void_LCDWriteString((u8*)" M ");
		
}
void APP_Void_LcdScreenWarning(){
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDGoTo(2,0);
	H_Lcd_Void_LCDWriteString((u8*)" !!!! WARNING !!!!");
}


