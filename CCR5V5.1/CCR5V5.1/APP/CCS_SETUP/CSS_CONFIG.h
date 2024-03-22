 /*
 * CRUIS_CONTROL_FLAGS.h
 *
 * Created: 3/4/2024 2:48:59 PM
 *  Author: seif
 */ 


#ifndef CRUIS_CONTROL_FLAGS_H_
#define CRUIS_CONTROL_FLAGS_H_ 
#include "LED_Interface.h"
#include "PushButton_Interface.h"
/********************************LCD STATUS**********************************/

#define GEAR_BOX_STATUS_N 'N'
#define GEAR_BOX_STATUS_R 'R'
#define GEAR_BOX_STATUS_D 'D' 

/*****************************BRAKE STATUS**********************************/
#define BRAKE_BUTTON_PRESSED 0
#define BRAKE_BUTTON_RELEASED 1
/*****************************CRUISE STATUS*********************************/
#define CRUISE_STATUS_ON 1
#define CRUISE_STATUS_OFF 0
#define CRUISE_BUTTON_PRESSED 0
#define CRUISE_BUTTON_RELEASED 1
#define RND_COUNTER_STATUS_N 0
#define RND_COUNTER_STATUS_D 1
#define RND_COUNTER_STATUS_R 2
#define ALERT_LIGHT LED_YEL
#define BRAKE_LIGHT LED_RED
#define CCS_LIGHT LED_GRN
#define RND_fLAG_STATE_N 0
#define RND_fLAG_STATE_D 1
#define RND_fLAG_STATE_R 2
#define BRAKE_ASSIST_BUTTON '1'
#define BRAKE_BUTTON '2'
#define CRUISE_BUTTON '3'
#define GEAR_BOX_BUTTON PUSH_BUTTON_3 
#define BRAKE 2 
#define CRUISE 3
#define GEAR_BOX 4 
#define DISTANCE_COUNTER "Distance: "
#define RND_INITIALCONDITION "PRND: N"
#define CCS_INITIALCONDITION "CCS: OFF"
#define RND_D_CONDITION "PRND: D"
#define RND_N_CONDITION "PRND: N"
#define RND_R_CONDITION "PRND: R"
#define CSS_ON "CCS: ON "
#define CSS_OFF "CCS: OFF"
#define ACCIDENT "Accident     "
#define NO_ACCIDENT "No Accident"
#define GAS_ENABLE 1
#define GAS_NEGLECT 0
#define BRAKE_ASSIST_OFF 0
#define BRAKE_ASSIST_ON 1
#define BRAKE_ON 1
#define BRAKE_OFF 0
#endif /* CRUIS_CONTROL_FLAGS_H_ */
