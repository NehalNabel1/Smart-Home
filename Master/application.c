/* 
 * File:   application.c
 * Author: Nehal
 *
 * Created on July 25, 2023, 10:21 PM
 */


#include "application.h"
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/USART/hal_usart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"
#include "ECU_Layer/RealTimeClockDS1307/RealTimeClockDS1307.h"
#include "ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.h"
uint8 Read_Password(void);
uint8 Check_Password(void);
Std_ReturnType ret= E_NOT_OK;
RealTimeClockDS1307_T RealTimeClockDS1307;
volatile uint8 keypadvalue=0;
volatile uint8 i=0;
volatile uint8 check=0 ,check2 =0 ,check3=0 , check4=0 ,check5=0;
volatile uint8 password_check=0;
uint8 Password[5]={'1','2','3','4','5'};




int main() {
   
    application_intialize();
    
       for(int j=0;j<5;j++){
       EEPROM_24C02C_Write_Byte(0xA2 ,(0x08 +j) ,Password[j]); 
    }
   
    __delay_us(100);
    EEPROM_24C02C_Write_Byte(0xA6 ,0x08 , 6);
    __delay_us(100);
   
   
     ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"To Enter Password ");
     ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Click *");
        
    while(1){
         
     ret=keypad_get_value(&keypad1,&keypadvalue);
     if(keypadvalue == '*'){
         Check_Password();
          
         ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
           
         
           
           check3=1;
     }
     
     if(check3==1){
         keypadvalue=0;
         while(1){
          
          
     /********************************************************user choice*****************************************************************/             
         ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"1 For Room1");
         ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"2 For Room2");
         ret=lcd_8bit_send_string_pos(&lcd_2,3,1,"3 To show the date");
         ret=lcd_8bit_send_string_pos(&lcd_2,4,1,"and time");
        
          
          ret=keypad_get_value(&keypad1,&keypadvalue);  
       
         if (keypadvalue == '1'){
            keypadvalue=0;
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            while(keypadvalue == 0){
            
            ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"1 To Open Door");
            ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"2 To Open Lamp");
            ret=lcd_8bit_send_string_pos(&lcd_2,3,1,"3 To Open TV");
            __delay_ms(200);
            ret=keypad_get_value(&keypad1,&keypadvalue);
            }
            if('1' == keypadvalue){
            keypadvalue=0;
            Door1_Open();
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 1 is Open");
            __delay_ms(400);
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
            else if('2' == keypadvalue){
                keypadvalue=0;
                ret= relay_turn_on(&relay1);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
                ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 1 Lamp is Open");
                __delay_ms(400);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
            else if('3' == keypadvalue){
                 keypadvalue=0;
                ret=led_turn_on(&led1);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
                ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 1 TV is Open");
                 __delay_ms(400);
                 ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
             
         }
         else if (keypadvalue == '2'){
             keypadvalue=0; 
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
             while(keypadvalue == 0){
            ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"1 To Open Door");
            ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"2 To Open Lamp");
            ret=lcd_8bit_send_string_pos(&lcd_2,3,1,"3 To Open TV");
             __delay_ms(200);
            ret=keypad_get_value(&keypad1,&keypadvalue);
           
             }
            if('1' == keypadvalue){
            keypadvalue=0;    
            Door2_Open();
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 2 is Open");
            __delay_ms(400);
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
            else if('2' == keypadvalue){
                keypadvalue=0;
                ret= relay_turn_on(&relay2);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
                ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 2 Lamp is Open");
                __delay_ms(400);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
            else if('3' == keypadvalue){
                keypadvalue=0;
                ret=led_turn_on(&led2);
                ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
                ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Room 2 TV is Open");
                 __delay_ms(400);
                 ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            }
               
             
             
         }
         else if('3' == keypadvalue){
            keypadvalue=0;
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
            while(keypadvalue !='*'){
            
            RealTimeClockDS1307= RealTimeClockDS1307_Get_Date_Time();
            Print_RealTimeClockDS1307();
            __delay_ms(20);
            ret=lcd_8bit_send_string_pos(&lcd_2,3,1,"* To Exit");
            ret=keypad_get_value(&keypad1,&keypadvalue);
            
            }
            ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
         }
         else{
              keypadvalue=0;
         }
        
        
         
         
     }
     }
     
  
        
    } 
    return (EXIT_SUCCESS);

}

void application_intialize(void){
  ecu_layer_intialize();
  
  
}
/**********************************************************************Read Password*******************************************************/
uint8 Read_Password(void){
     keypadvalue= 0;
     ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
      __delay_ms(200);
     ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Password : ");
     
    while(i!=5){
        ret=keypad_get_value(&keypad1,&keypadvalue);
       if(keypadvalue != 0) {       
       ret=lcd_8bit_send_string_pos(&lcd_2,1,(12+i),"*");
       __delay_ms(500);
       
       if(Password[i]!= keypadvalue){
           check=1;
       }
       i++;
       } 
        keypadvalue= 0; 
     }
    return check;
}
/**********************************************************************Check Password**************************************************************/
uint8 Check_Password(void){
    password_check =Read_Password();
     
     while(check2 != 1){         
     
     if(password_check==1){
         ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
          __delay_ms(200);
      ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Wrong Password !");
      ret=lcd_8bit_send_string_pos(&lcd_2,2,1,"Try Again");
      __delay_ms(800);
       ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);       
      
      i=0;
      check=0;
      password_check =Read_Password();
     }
     else if(password_check == 0){
         check2 =1;
         ret=lcd_8bit_send_command (&lcd_2,_LCD_CLEAR);
         ret=lcd_8bit_send_string_pos(&lcd_2,1,1,"Correct Password !");
        __delay_ms(500);
     }
     }
    
}



      



