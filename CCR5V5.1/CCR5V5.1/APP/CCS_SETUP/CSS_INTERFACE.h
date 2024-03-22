/*
 * APP.h
 *
 *  Created on: Mar 4, 2024
 *      Author: tarek
 */

#ifndef APP_APP_H_
#define APP_APP_H_
#include "EXTINT_Interface.h"
#include "ADC_Interface.h"
#include "CSS_CONFIG.h"
#include "LCD_Interface.h"
#include "Buzzer_Interface.h"
#include "PushButton_Interface.h"
#include "Keypad_Interface.h"
#include "Relay_Interface.h" 

extern u8 brake_flag;

void GEARBOX_PRESSED_NOTIFICATION_BUZZER(void);
void CCS_PRESSED_NOTIFICATION_BUZZER(void);

void system_CCS_init(void); 


void brake_serviceFun(void);

void CSS_serviceFun(void); 
void ccs_turn_Off(void);
void ccs_turn_On(void);
void gear_box_RND_update_state(void);  
void brake_assist_system(void);
//u8 CSS_GET_STATES_ofBUTTONS (void);
 
#endif /* APP_APP_H_ */
