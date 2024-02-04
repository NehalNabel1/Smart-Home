/* 
 * File:   application.c
 * Author: Nehal
 *
 * Created on July 25, 2023, 10:21 PM
 */


#include "application.h"
#include "MCAL_Layer/USART/hal_usart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"
#include "ECU_Layer/ecu_layer_init.h"
#include "ECU_Layer/TemSensor_TC74/TemSensor_TC74.h"



Std_ReturnType ret= E_NOT_OK;
volatile uint8 check1=0,check2=0,check3=0;
uint16 adc_lm35_1=0 ,adc_lm35_celsius=0;
uint8 adc_lm35_1_txt[7];

 


volatile uint8 i=0;

int main() {
   
      
    application_intialize();
   
       
    
    while(1){
       
      ret=ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&adc_lm35_1) ;      
       adc_lm35_celsius=adc_lm35_1* 4.88f;
       adc_lm35_celsius/=10;
        ret=convert_uint16_to_string( adc_lm35_celsius,adc_lm35_1_txt);
       ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Temperature : ");       
        ret=lcd_8bit_send_string_pos(&lcd_2,1,14,adc_lm35_1_txt);
        __delay_ms(50);
        if ( adc_lm35_celsius >30){
            check2=0;
            check3=0;
            if(check1==0){
             ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Temperature : ");
             ret=ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&adc_lm35_1) ;           
             adc_lm35_celsius=adc_lm35_1*4.88f;
             adc_lm35_celsius/=10;
             ret=convert_uint16_to_string( adc_lm35_celsius,adc_lm35_1_txt);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,14,adc_lm35_1_txt);
             check1=1;
            }
            ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Fan ON ");
            ret=dc_motor_move_right(&dc_motor1);
            ret=dc_motor_stop(&dc_motor2);
            
        }
        else if( adc_lm35_celsius<20){
            check1=0;
            check3=0;
             ret=dc_motor_move_right(&dc_motor2);
             ret=dc_motor_stop(&dc_motor1);
             if(check2==0){
             ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Temperature : ");
             ret=ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&adc_lm35_1) ;           
             adc_lm35_celsius=adc_lm35_1*4.88f;
             adc_lm35_celsius/=10;
             ret=convert_uint16_to_string( adc_lm35_celsius,adc_lm35_1_txt);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,14,adc_lm35_1_txt);
             check2=1;
             
            }
             ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Heater ON ");
             
             
        }
        else {
             check1=0;
             check2=0;
             ret=dc_motor_stop(&dc_motor1);
             ret=dc_motor_stop(&dc_motor2);
             if(check3==0){
             ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Temperature : ");
             ret=ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&adc_lm35_1) ;           
             adc_lm35_celsius=adc_lm35_1 * 4.88f;
             adc_lm35_celsius/=10;
             ret=convert_uint16_to_string( adc_lm35_celsius,adc_lm35_1_txt);
             ret=lcd_8bit_send_string_pos(&lcd_2,1,14,adc_lm35_1_txt);
             check3=1;
            }
             ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Fan OFF / Heater OFF ");
            
             
        }
        
      
   
   }     
        
     
    return (EXIT_SUCCESS);
}

void application_intialize(void){
 ecu_layer_intialize();
  
  
}




