/*
 * CSS.c
 *
 *  Created on: Mar 5, 2024
 *      Author: tarek
 */


#define F_CPU 16000000UL
#include "CSS_INTERFACE.h"

/*************************************************************************************************** *
*											GLOBAL VARIABLES										 *
******************************************************************************************************/
u8 brake_flag=BRAKE_OFF;

/*************************************************************************************************** *
*											GLOBAL FUNCTIONS										 *
******************************************************************************************************/

void CCS_PRESSED_NOTIFICATION_BUZZER()
{
	H_Buzzer_Void_BuzzerOnce();
}
/*CCS_PRESSED_NOTIFICATION_BUZZER is just a function
 * to turn on the buzzer for 80 milli-seconds twice */
void GEARBOX_PRESSED_NOTIFICATION_BUZZER()
{
	H_Buzzer_Void_BuzzerTwice();
}

void system_CCS_init(void) {
	/******************************************LOCAL VARIABLES********************************************/
	H_Lcd_Void_LCDInit();
	H_KeyPad_Void_KeyPadInit();
	/******************************************INITIALIZE BUZZER********************************************/
	H_Buzzer_Void_BuzzerInit();
	/******************************************INITIALIZE ADC********************************************/
	M_ADC_Void_ADCInit();
	/************************************SET LED PINS DIRECTION AS OUTPUTS********************************/
	H_LED_Void_LedInit(BRAKE_LIGHT);
	H_LED_Void_LedInit(ALERT_LIGHT);
	H_relay_INIT();
	/***********************************INITIALIZE ALL THE LED PINS WITH A LOGIC LOW**********************/
	//H_LED_Void_LedOff(GAS_LIGHT);
	H_LED_Void_LedOff(BRAKE_LIGHT);
	H_LED_Void_LedOff(ALERT_LIGHT);
	H_relay_OFF();
	/************************************SET SWITCH PINS DIRECTION AS INPUTS******************************/
	H_PushButton_Void_PushButtonInit(GEAR_BOX_BUTTON);
	M_DIO_Void_SetPinValue(GEAR_BOX_BUTTON, HIGH);
	/***********************************INITIALIZE EXTERNAL INTERRUPT1************************************/
	M_EXTINT_Void_EXTINTInit(INT1_CHANNEL);
	M_DIO_Void_SetPinDirection(PC7_PIN,OUTPUT);
}

/***************************************IMPLEMENTING THE BRAKE SERVICE FUNCTION**********************/
void brake_serviceFun(void) {
	/***************************************AS LONG AS THE BRAKE BUTTON IS pRESSED, THE BRAKE LED IS ON****/
		while (H_KeyPad_U8_KeyPadRead() == '2') {
			H_LED_Void_LedOn(BRAKE_LIGHT);
			brake_flag=BRAKE_ON;
		}
		H_LED_Void_LedOff(BRAKE_LIGHT);
		brake_flag=BRAKE_OFF;
}

// /***************************************IMPLEMENTING THE GEAR BOX SERVICE FUNCTION******************/
// void gear_box_RND_update_state(void) {
// 
// 	if(brake_flag==BRAKE_ON) {         /******* CHECK IF BRAKE IS PRESSED **********/
// 			RND_flag++;
// 			if(RND_flag>RND_fLAG_STATE_R){          /***** REWIND GEAR BOX****/
// 				RND_flag=RND_fLAG_STATE_N;
// 			}
// 		switch (RND_flag) {
// 		case RND_fLAG_STATE_N:              /******* TURN STATE TO N AND TURN OFF CCS********/
// 			GEARBOX_PRESSED_NOTIFICATION_BUZZER();
// 			H_Lcd_Void_LCDGoTo(1, 0);
// 			H_Lcd_Void_LCDWriteString(RND_N_CONDITION);
// 			ccs_turn_Off();
// 			while (H_PushButton_U8_PushButtonRead(GEAR_BOX_BUTTON) == PUSH_BUTTON_PRESSED);
// 			break;
// 		case RND_fLAG_STATE_D:              /******* TURN STATE TO D********/
// 			//GEARBOX_PRESSED_NOTIFICATION_BUZZER();
// 			H_Lcd_Void_LCDGoTo(1, 0);
// 			H_Lcd_Void_LCDWriteString(RND_D_CONDITION);
// 			while (H_PushButton_U8_PushButtonRead(GEAR_BOX_BUTTON) == PUSH_BUTTON_PRESSED);
// 			break;
// 		case RND_fLAG_STATE_R:               /******* TURN STATE TO R AND TURN OFF CCS********/
// 			GEARBOX_PRESSED_NOTIFICATION_BUZZER();
// 			H_Lcd_Void_LCDGoTo(1, 0);
// 			H_Lcd_Void_LCDWriteString(RND_R_CONDITION);
// 			ccs_turn_Off();
// 			while (H_PushButton_U8_PushButtonRead(GEAR_BOX_BUTTON) == PUSH_BUTTON_PRESSED);
// 			break;
// 		default:
// 			break;
// 		}
// 	}
// 	else
// 	{
// 		while (H_PushButton_U8_PushButtonRead(GEAR_BOX_BUTTON) == PUSH_BUTTON_PRESSED){      /****** IF PRESSED WITHOUT BRAKE TURN ON ALERT LIGHT******/
// 				H_LED_Void_LedOn(ALERT_LIGHT);
// 		}
// 		H_LED_Void_LedOff(ALERT_LIGHT);
// 	}
// }

// void brake_assist_system(void){
// //	cli();
// 
// 	if((RND_flag==RND_COUNTER_STATUS_D)&&(brake_assist_flag==BRAKE_ASSIST_ON)){
// 	distance=(u32)M_ADC_U16_ADCRead(ADC_CHANNEL_0)*200/40;
// 	H_Lcd_Void_LCDGoTo(2, 10);
// 	H_Lcd_Void_LCDWriteNumber(distance);
// 	H_Lcd_Void_LCDWriteCharacter(' ');
// 	if(distance>=8){
// 		H_LED_Void_LedOff(ALERT_LIGHT);
// 		H_LED_Void_LedOff(BRAKE_LIGHT);
// 		H_Lcd_Void_LCDGoTo(3,0);
// 		H_Lcd_Void_LCDWriteString(NO_ACCIDENT);
// 		gas_flag=GAS_ENABLE;
// 	}
// 	else if(distance>=6){
// 		H_LED_Void_LedOn(ALERT_LIGHT);
// 		H_LED_Void_LedOff(BRAKE_LIGHT);
// 		H_Lcd_Void_LCDGoTo(3,0);
// 		H_Lcd_Void_LCDWriteString(NO_ACCIDENT);
// 		if (CSS_flag == CRUISE_STATUS_OFF){
// 			ccs_turn_Off();
// 		}
// 		gas_flag=GAS_NEGLECT;
// 	}
// 	else if(distance>=4){
// 		H_LED_Void_LedOn(ALERT_LIGHT);
// 		H_LED_Void_LedOn(BRAKE_LIGHT);
// 		H_Lcd_Void_LCDGoTo(3,0);
// 		H_Lcd_Void_LCDWriteString(NO_ACCIDENT);
// 		if (CSS_flag == CRUISE_STATUS_OFF){
// 			ccs_turn_Off();
// 		}
// 		gas_flag=GAS_NEGLECT;
// 	}
// 	else if(distance>=2){
// 			H_LED_Void_LedOn(BRAKE_LIGHT);
// 			H_LED_Void_LedTog(ALERT_LIGHT);
// 			H_Lcd_Void_LCDGoTo(3,0);
// 			H_Lcd_Void_LCDWriteString(NO_ACCIDENT);
// 			if (CSS_flag == CRUISE_STATUS_OFF){
// 				ccs_turn_Off();
// 			}
// 
// 			gas_flag=GAS_NEGLECT;
// 		}
// 	else if(distance<2){
// 		/***relay fun***/
// 		H_LED_Void_LedOff(ALERT_LIGHT);
// 		H_LED_Void_LedOff(BRAKE_LIGHT);
// 
// 		//gas_flag=GAS_NEGLECT;
// 		H_Lcd_Void_LCDGoTo(3,0);
// 		H_Lcd_Void_LCDWriteString(ACCIDENT);
// 		if (CSS_flag == CRUISE_STATUS_OFF){
// 			ccs_turn_Off();
// 		}
// 		M_DIO_Void_SetPinValue(PC7_PIN,HIGH);
// 		_delay_ms(700);
// 		M_DIO_Void_SetPinValue(PC7_PIN,LOW);
// 	}
// 	}
// 	//sei();
// }
