/* 
 * File:   seven_segment.h
 * Author: Nehal
 *
 * Created on September 4, 2023, 3:23 PM
 */

#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

/* Section : Includes*/
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3
/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */
typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE      
    
}segment_type_t;

typedef struct {
    pin_config_t  segment_pins[4];
    segment_type_t segment_type;
}segmen_t;


/* Section : Function Declarations */
Std_ReturnType seven_segment_initialize(const segmen_t *seg);
Std_ReturnType seven_segment_write_number(const segmen_t *seg ,uint8 number);

#endif	/* SEVEN_SEGMENT_H */

