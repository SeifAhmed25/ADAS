/*
 * DRIV_MONITORING.c
 *
 * Created: 3/17/2024 9:21:35 PM
 *  Author: seif
 */ 
#include "DRIV_MONITORING_INTERFACE.h" 

u8 Driv_monitoring_status_flag = 0; 
u8 Inactive_counter = 0;
void APP_Void_DrivMonitoringUpdateFlag (){
	if (Driv_monitoring_status_flag == DRIV_MONITORING_OFF){
		Driv_monitoring_status_flag = DRIV_MONITORING_ON; 
	}
	else if (Driv_monitoring_status_flag == DRIV_MONITORING_ON){
		Driv_monitoring_status_flag = DRIV_MONITORING_OFF;
	}
}
