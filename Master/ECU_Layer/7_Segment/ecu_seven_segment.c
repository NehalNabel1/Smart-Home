/* 
 * File:   seven_segment.c
 * Author: Nehal
 *
 * Created on September 4, 2023, 3:23 PM
 */

#include "ecu_seven_segment.h"

/**
 * @brief Initialize the assigned pins to be OUTPUT
 * @param seg pointer to the seven segment configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segmen_t *seg){
    Std_ReturnType ret=E_OK;
    
    if(NULL== seg){
        ret=E_NOT_OK;
    }
    else {
        ret=gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret=gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret=gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret=gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN3]));
        
    }
    
    return ret;
    
}
/**
 * @brief Write number on the seven segment
 * @param seg pointer to the seven segment configurations
 * @param number
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segmen_t *seg ,uint8 number){
    
    Std_ReturnType ret=E_OK;
    
    if((NULL== seg ) || (number > 9)){
        ret=E_NOT_OK;
    }
    else {
        ret=gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]),number & 0x01);
        ret=gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]),(number>>1) & 0x01);
        ret=gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]),(number>>2) & 0x01);
        ret=gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]),(number>>3) & 0x01);
        
    }
    
    return ret;
    
    
}
