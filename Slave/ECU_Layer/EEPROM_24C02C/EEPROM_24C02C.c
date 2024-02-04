/* 
 * File:   EEPROM_24C02C.c
 * Author: Nehal
 *
 * Created on December 9, 2023, 8:27 PM
 */
#include"EEPROM_24C02C.h"
Std_ReturnType ret= E_NOT_OK;
void EEPROM_24C02C_Write_Byte(uint8 EEPROM_Address,uint8 Byte_Address ,uint8 Data){
    uint8 data_read;
    uint8 slave_ack;
    ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,EEPROM_Address,&slave_ack);
    __delay_ms(10)   ;
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,Byte_Address,&slave_ack);
    __delay_ms(10)   ;
    ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,Data,&slave_ack);
    __delay_ms(10)   ;
    ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ; 
    
}
uint8 EEPROM_24C02C_Read_Byte(uint8 EEPROM_Address,uint8 Byte_Address ){
    
    uint8 data_read;
    uint8 slave_ack;

   ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,EEPROM_Address,&slave_ack);
    __delay_ms(10)   ;
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,Byte_Address,&slave_ack);
    __delay_ms(10)   ;
      ret=MSSP_I2C_Master_Send_Repeated_Start(&i2c_obj); 
    __delay_ms(10)   ;
       ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,(EEPROM_Address + 1),&slave_ack);
    __delay_ms(10)   ;    
    ret=MSSP_I2C_Master_Read_Blocking(&i2c_obj,I2C_MASTER_SEND_NACK,&data_read);
    __delay_ms(10)   ; 
     ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ;   
    return data_read;

}