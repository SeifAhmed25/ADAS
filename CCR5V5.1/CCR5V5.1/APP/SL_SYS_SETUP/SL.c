/*
 * SL.c
 *
 *  Created on: Mar 16, 2024
 *      Author: tarek
 */


#include "SL_Interface.h" 

u8 SL_STATUS_FLAG = SL_BUTTON_STATUS_OFF;
u8 gas_serviceFun(void) {
	u8 speed=(u8)M_ADC_U16_ADCRead(ADC_CHANNEL_0)*MAX_SPEED/MAX_ANGLE;
	if(speed>MAX_SPEED){
		speed=MAX_SPEED;
	}
	return speed;	
} 
void Speed_Limiter_Alarm_function(void)
{
	H_relay_Tog();
}
