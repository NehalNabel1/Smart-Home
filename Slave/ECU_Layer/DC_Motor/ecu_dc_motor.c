/* 
 * File:   ecu_dc_motor.c
 * Author: Nehal
 *
 * Created on September 2, 2023, 3:33 PM
 */

#include "ecu_dc_motor.h"

/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON
 * @param _motor pointer to the motor configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */

Std_ReturnType dc_motor_initialize(const dc_motor_t *_motor){
    Std_ReturnType ret=E_OK;
    if(NULL== _motor){
        ret=E_NOT_OK;
    }
    else {       
               
        gpio_pin_intialize(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_intialize(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]));
        }
    
    return ret;   
    
}
/**
 * @brief Move the motor to the right direction
 * @param _motor pointer to the motor configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_motor){
    Std_ReturnType ret=E_OK;
    if(NULL== _motor){
        ret=E_NOT_OK;
    }
    else {
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_HIGH);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
        
    }
    
    return ret;
    
    
    
}
/**
 * @brief Move the motor to the left direction
 * @param _motor pointer to the motor configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_motor){
    Std_ReturnType ret=E_OK;
    if(NULL== _motor){
        ret=E_NOT_OK;
    }
    else {           
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_HIGH);
       
        
    }
    
    return ret;
    
    
    
}
/**
 * @brief Stop the motor 
 * @param _motor pointer to the motor configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_motor){
    Std_ReturnType ret=E_OK;
    if(NULL== _motor){
        ret=E_NOT_OK;
    }
    else {        
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
        
    }
    
    return ret;
    
    
    
}
