/* 
 * File:   ecu_layer_init.h
 * Author: Nehal
 *
 * Created on September 4, 2023, 10:21 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes*/
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_segment.h"
#include "Keypad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"
#include "EEPROM_24C02C/EEPROM_24C02C.h"
#include "RealTimeClockDS1307/RealTimeClockDS1307.h"
#include "../MCAL_Layer/CCP1/hal_ccp1.h"
#include "../MCAL_Layer/Timer2/hal_timer2.h"
#include "../MCAL_Layer/Timer3/hal_timer3.h"
#include "../MCAL_Layer/ADC/hal_adc.h"


/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
void ecu_layer_intialize(void);
void CCP1_DefaultInterruptHandler(void) ;
#endif	/* ECU_LAYER_INIT_H */

