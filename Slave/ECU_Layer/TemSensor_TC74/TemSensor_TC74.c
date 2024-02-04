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
    uint8 slave_ack;

   ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,TC74_Address,&slave_ack);
    __delay_ms(10)   ;
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,0x00,&slave_ack);
    __delay_ms(10)   ;
      ret=MSSP_I2C_Master_Send_Repeated_Start(&i2c_obj); 
    __delay_ms(10)   ; 
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,(TC74_Address+1),&slave_ack);    
    __delay_ms(10)   ;        
    ret=MSSP_I2C_Master_Read_Blocking(&i2c_obj,I2C_MASTER_SEND_NACK,&Temp_Value);
    __delay_ms(10)   ; 
     ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ;   
    
    
    return Temp_Value;
}
