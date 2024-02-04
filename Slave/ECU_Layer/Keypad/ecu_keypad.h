/* 
 * File:   ecu_keypad.h
 * Author: Nehal
 *
 * Created on September 4, 2023, 8:59 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/* Section : Macro Declarations */
#define ECU_KEYPAD_ROW 4
#define ECU_KEYPAD_COLUMNS 4
/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */
typedef struct {
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW] ;
    pin_config_t keypad_coulmn_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;
/* Section : Function Declarations */

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj ,uint8 *value);

#endif	/* ECU_KEYPAD_H */

