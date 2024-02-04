/* 
 * File:   ecu_relay.c
 * Author: Nehal
 *
 * Created on September 1, 2023, 4:24 PM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    
    if(NULL== _relay){
        ret=E_NOT_OK;
    }
    else {
        pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.logic=_relay->relay_status};
        gpio_pin_intialize(&pin_obj);
        
        
    }
    
    return ret;
    
    
}
/**
 * Turn the led on.
 * @param _relay pointer to the relay configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    
    if(NULL== _relay){
        ret=E_NOT_OK;
    }
    else {
        pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.logic=_relay->relay_status};
        
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
        
        
    }
    
    return ret;
    
    
}
/**
 * Turn the relay off.
 * @param _relay pointer to the relay configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret=E_OK;
    
    if(NULL== _relay){
        ret=E_NOT_OK;
    }
    else {
        pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.logic=_relay->relay_status};
        
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
        
        
    }
    
    return ret;
    
    
}
