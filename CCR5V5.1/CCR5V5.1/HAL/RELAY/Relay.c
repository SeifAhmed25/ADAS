/*
 * Relay.c
 *
 * Created: 3/17/2024 1:57:54 PM
 *  Author: seif
 */ 
#include "Relay_Interface.h"
void H_relay_INIT(void){
	M_DIO_Void_SetPinDirection(RELAY_PIN,OUTPUT);
}
void H_relay_Tog(void){
	M_DIO_Void_TogPin(RELAY_PIN);
}
void H_relay_OFF(void){
	M_DIO_Void_SetPinValue(RELAY_PIN,LOW);
}