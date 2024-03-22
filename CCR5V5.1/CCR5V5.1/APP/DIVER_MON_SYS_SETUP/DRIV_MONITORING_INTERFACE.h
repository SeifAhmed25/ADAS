/*
 * DRIV_MONITORING_INTERFACE.h
 *
 * Created: 3/17/2024 9:22:05 PM
 *  Author: seif
 */ 


#ifndef DRIV_MONITORING_INTERFACE_H_
#define DRIV_MONITORING_INTERFACE_H_
#include "STD.h"
#include "DRIV_MONITORING_CONFIG.h"

extern u8 Driv_monitoring_status_flag; 
extern u8 Inactive_counter;
void APP_Void_DrivMonitoringUpdateFlag (void);


#endif /* DRIV_MONITORING_INTERFACE_H_ */
