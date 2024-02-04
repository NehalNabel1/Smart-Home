/* 
 * File:   application.h
 * Author: Dubai
 *
 * Created on July 26, 2023, 6:53 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/* Section : Includes*/
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
# include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"


/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

extern led_t led1;
extern chr_lcd_8bit_t lcd_2;
chr_lcd_4bit_t lcd_1;
extern dc_motor_t dc_motor1 ;
extern dc_motor_t dc_motor2 ;
extern ccp_t ccp1_obj;
extern timer3_t timer_obj;
extern relay_t relay; 
extern  adc_conf_t adc_1;
/* Section : Function Declarations */
void application_intialize(void);
void Int0_APP_ISR();

#endif	/* APPLICATION_H */

