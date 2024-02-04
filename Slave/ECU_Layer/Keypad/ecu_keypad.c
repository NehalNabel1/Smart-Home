/* 
 * File:   ecu_keypad.c
 * Author: Nehal
 *
 * Created on September 4, 2023, 8:59 PM
 */

#include "ecu_keypad.h"


static const uint8 btn_value[ECU_KEYPAD_ROW][ECU_KEYPAD_COLUMNS]={
                                                                    {'7','8','9','/'},
                                                                    {'4','5','6','*'},
                                                                    {'1','2','3','-'},
                                                                    {'#','0','=','+'}                                                          
                                                                  };
              /**
 * @brief Initialize the assigned pins to be INPUT or OUTPUT
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret=E_OK;
    uint8 rows_counter=ZERO_INIT,coulmns_counter=ZERO_INIT;
    if(NULL == _keypad_obj){
        ret=E_NOT_OK;
    }
    else {
        for(rows_counter=ZERO_INIT;rows_counter < ECU_KEYPAD_ROW;rows_counter++){
            ret=gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(coulmns_counter=ZERO_INIT;coulmns_counter < ECU_KEYPAD_COLUMNS;coulmns_counter++){
            ret=gpio_pin_direction_intialize(&(_keypad_obj->keypad_coulmn_pins[coulmns_counter]));
        }
        
        
        
    }
    
    return ret;
    
    
}
/**
 * @brief get value from keypad
 * @param _keypad_obj pointer to the keypad configurations
 * @param value pointer to keypad value
 * @return Status of the function 
 *     (E_OK):the function done successfully 
 *     (E_NOT_OK):the function has issue to perform this action
 */

Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj ,uint8 *value){
    
    Std_ReturnType ret=E_OK;
    uint8 coulmn_logic=ZERO_INIT ;
    uint8 l_rows_counter=ZERO_INIT,l_coulmns_counter=ZERO_INIT ,l_counter=ZERO_INIT;
    if((NULL == _keypad_obj) || (NULL ==value)){
        ret=E_NOT_OK;
    }
    else {
        for(l_rows_counter=ZERO_INIT;l_rows_counter < ECU_KEYPAD_ROW;l_rows_counter++){
            for(l_counter=ZERO_INIT;l_counter < ECU_KEYPAD_ROW;l_counter++){
               ret= gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]),GPIO_LOW);           
            
            }
             gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]),GPIO_HIGH); 
             
             for(l_coulmns_counter=ZERO_INIT;l_coulmns_counter < ECU_KEYPAD_COLUMNS;l_coulmns_counter++){ 
               ret= gpio_pin_read_logic(&(_keypad_obj->keypad_coulmn_pins[l_coulmns_counter]) ,& coulmn_logic);
               
               if(GPIO_HIGH == coulmn_logic){
                   *value= btn_value[l_rows_counter][l_coulmns_counter];
               }
             }
            
        
    }
    }
    
    return ret;
    
    
}
