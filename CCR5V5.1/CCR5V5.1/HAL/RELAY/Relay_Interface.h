/*
 * Relay_Interface.h
 *
 * Created: 3/17/2024 1:58:14 PM
 *  Author: seif
 */ 


#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_
#include "Relay_Config.h"
#include "STD.h"
#include "DIO_Interface.h"
void H_relay_INIT(void);
void H_relay_Tog(void);
void H_relay_OFF(void);



#endif /* RELAY_INTERFACE_H_ */