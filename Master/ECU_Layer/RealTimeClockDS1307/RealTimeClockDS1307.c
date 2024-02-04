/* 
 * File:   RealTimeClockDS1307.h
 * Author: Nehal
 *
 * Created on November 30, 2023, 8:52 PM
 */
#include"RealTimeClockDS1307.h"

Std_ReturnType ret= E_NOT_OK;
static RealTimeClockDS1307_T RealTimeClockDS1307;
 uint8 RealTimeClockDS1307_Data[9];
 uint8 RealTimeClockDS1307_Str_Data[9];
 uint8 RealTimeClockDS1307_Time[9];

 static volatile uint8 check4=0;

static uint8 Read_RealTimeClockDS1307(uint8 add){
    uint8 data_read;
    uint8 slave_ack;

   ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,0xD0,&slave_ack);
    __delay_ms(1)   ;
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,add,&slave_ack);
    __delay_ms(1)   ;
      ret=MSSP_I2C_Master_Send_Repeated_Start(&i2c_obj); 
    __delay_ms(1)   ;
       ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,0xD1,&slave_ack);
    __delay_ms(10)   ;    
    ret=MSSP_I2C_Master_Read_Blocking(&i2c_obj,I2C_MASTER_SEND_NACK,&data_read);
    __delay_ms(1)   ; 
     ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ;   
    return data_read;
}





RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void){
    uint8 slave_ack;
    uint8 _data;
    
    
    RealTimeClockDS1307._Seconds= Read_RealTimeClockDS1307(0x00);
    RealTimeClockDS1307._Minutes= Read_RealTimeClockDS1307(0x01);
    RealTimeClockDS1307._Hours= Read_RealTimeClockDS1307(0x02);
    RealTimeClockDS1307._Day= Read_RealTimeClockDS1307(0x04);
    RealTimeClockDS1307._Month= Read_RealTimeClockDS1307(0x05);
    RealTimeClockDS1307._Year= Read_RealTimeClockDS1307(0x06);
    
   
    return RealTimeClockDS1307;
    
}

void Print_RealTimeClockDS1307(void){
   
    RealTimeClockDS1307_Data[0]= ((RealTimeClockDS1307._Day >> 4) + 0x30);
    
    RealTimeClockDS1307_Data[1]= ((RealTimeClockDS1307. _Day& 0x0F) +0x30);
    RealTimeClockDS1307_Data[2]='-';
    RealTimeClockDS1307_Data[3]= ((RealTimeClockDS1307._Month>> 4) + 0x30);
    RealTimeClockDS1307_Data[4]= ((RealTimeClockDS1307._Month& 0x0F) +0x30);
    RealTimeClockDS1307_Data[5]='-';
    RealTimeClockDS1307_Data[6]= ((RealTimeClockDS1307._Year >> 4) + 0x30);
    RealTimeClockDS1307_Data[7]= ((RealTimeClockDS1307._Year& 0x0F) +0x30);
    RealTimeClockDS1307_Data[8]='\0';
    RealTimeClockDS1307_Time[0]= ((RealTimeClockDS1307._Hours >> 4) + 0x30);
     
    RealTimeClockDS1307_Time[1]= ((RealTimeClockDS1307._Hours& 0x0F) +0x30);
    RealTimeClockDS1307_Time[2]=':';
    RealTimeClockDS1307_Time[3]= ((RealTimeClockDS1307._Minutes >> 4) + 0x30);
    RealTimeClockDS1307_Time[4]= ((RealTimeClockDS1307._Minutes& 0x0F) +0x30);
    RealTimeClockDS1307_Time[5]=':';
    RealTimeClockDS1307_Time[6]= ((RealTimeClockDS1307._Seconds>> 4) + 0x30);
    RealTimeClockDS1307_Time[7]= ((RealTimeClockDS1307._Seconds& 0x0F) +0x30);
    RealTimeClockDS1307_Time[8]='\0';
   
    
   
    ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Date : ");
    ret=lcd_8bit_send_string_pos(&lcd_2,1,8,&RealTimeClockDS1307_Data);
    
   
    ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Time : ");
    ret=lcd_8bit_send_string_pos(&lcd_2,2,8,&RealTimeClockDS1307_Time);
           
           
    
    
}

