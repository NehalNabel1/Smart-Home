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
extern keypad_t keypad1;
extern led_t led1;
extern chr_lcd_8bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;
extern timer3_t timer_obj;
extern timer1_t timer1_obj;
extern ccp_t ccp1_obj;
extern ccp_t ccp2_obj;
extern relay_t relay1;
extern relay_t relay2;
extern led_t led1;
extern led_t led2;

/* Section : Function Declarations */
void application_intialize(void);



#endif	/* APPLICATION_H */

