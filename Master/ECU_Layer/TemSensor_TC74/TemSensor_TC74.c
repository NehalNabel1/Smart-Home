/* 
 * File:   TemSensor_TC74.c
 * Author: Nehal
 *
 * Created on December 10, 2023, 10:50 AM
 */

#include "TemSensor_TC74.h"
Std_ReturnType ret= E_NOT_OK;
uint8 TemSensor_TC74_Read_Temp(uint8 TC74_Address){
    uint8 Temp_Value ;   
     Temp_Value=I2C_Read_Register(&i2c_obj, TC74_Address,0x00);
    
    
    return Temp_Value;
}
