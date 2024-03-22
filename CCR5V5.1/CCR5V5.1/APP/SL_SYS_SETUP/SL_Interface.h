/*
 * SL_Interface.h
 *
 *  Created on: Mar 16, 2024
 *      Author: tarek
 */

#ifndef APP_SL_INTERFACE_H_
#define APP_SL_INTERFACE_H_
#include "STD.h"
#include "SL_Config.h"
#include "DIO_Interface.h"
#include "Keypad_Interface.h"
#include "ADC_Interface.h" 
#include "Relay_Interface.h"

extern u8 speed_limit;
extern u8 speed;
extern u8 SL_STATUS_FLAG; 

u8 gas_serviceFun(void); 
void Speed_Limiter_Alarm_function(void);

#endif /* APP_SL_INTERFACE_H_ */
