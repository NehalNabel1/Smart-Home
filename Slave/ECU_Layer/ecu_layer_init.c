/* 
 * File:   ecu_layer_init.c
 * Author: Nehal
 *
 * Created on September 4, 2023, 10:21 PM
 */
#include "ecu_layer_init.h"


usart_t usart_obj;
ccp_t ccp1_obj;
timer3_t timer_obj;
Std_ReturnType ret= E_NOT_OK;
volatile uint8 compare_flag=0;
uint8 ADC_Req=0;
chr_lcd_4bit_t lcd_1={
    .lcd_rs.port=PORC_INDEX,
    .lcd_rs.pin=PIN0,
    .lcd_rs.logic=GPIO_LOW,
    .lcd_rs.direction=GPIO_DIRECTION_OUTPUT,
    
    .lcd_en.port=PORC_INDEX,
    .lcd_en.pin=PIN1,
    .lcd_en.logic=GPIO_LOW,
    .lcd_en.direction=GPIO_DIRECTION_OUTPUT,
    
    
    .lcd_data[0].port=PORC_INDEX,
    .lcd_data[0].pin=PIN2,
    .lcd_data[0].logic=GPIO_LOW,
    .lcd_data[0].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].port=PORC_INDEX,
    .lcd_data[1].pin=PIN3,
    .lcd_data[1].logic=GPIO_LOW,
    .lcd_data[1].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].port=PORC_INDEX,
    .lcd_data[2].pin=PIN4,
    .lcd_data[2].logic=GPIO_LOW,
    .lcd_data[2].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].port=PORC_INDEX,
    .lcd_data[3].pin=PIN5,
    .lcd_data[3].logic=GPIO_LOW,
    .lcd_data[3].direction=GPIO_DIRECTION_OUTPUT    
       
};

chr_lcd_8bit_t lcd_2={
    .lcd_rs.port=PORB_INDEX,
    .lcd_rs.pin=PIN0,
    .lcd_rs.logic=GPIO_LOW,
    .lcd_rs.direction=GPIO_DIRECTION_OUTPUT,
    
    .lcd_en.port=PORTA_INDEX,
    .lcd_en.pin=PIN1,
    .lcd_en.logic=GPIO_LOW,
    .lcd_en.direction=GPIO_DIRECTION_OUTPUT,
    
    
    .lcd_data[0].port=PORD_INDEX,
    .lcd_data[0].pin=PIN0,
    .lcd_data[0].logic=GPIO_LOW,
    .lcd_data[0].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].port=PORD_INDEX,
    .lcd_data[1].pin=PIN1,
    .lcd_data[1].logic=GPIO_LOW,
    .lcd_data[1].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].port=PORD_INDEX,
    .lcd_data[2].pin=PIN2,
    .lcd_data[2].logic=GPIO_LOW,
    .lcd_data[2].direction=GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].port=PORD_INDEX,
    .lcd_data[3].pin=PIN3,
    .lcd_data[3].logic=GPIO_LOW,
    .lcd_data[3].direction=GPIO_DIRECTION_OUTPUT,  
    .lcd_data[4].port=PORD_INDEX,
    .lcd_data[4].pin=PIN4,
    .lcd_data[4].logic=GPIO_LOW,
    .lcd_data[4].direction=GPIO_DIRECTION_OUTPUT,  
    .lcd_data[5].port=PORD_INDEX,
    .lcd_data[5].pin=PIN5,
    .lcd_data[5].logic=GPIO_LOW,
    .lcd_data[5].direction=GPIO_DIRECTION_OUTPUT,  
    .lcd_data[6].port=PORD_INDEX,
    .lcd_data[6].pin=PIN6,
    .lcd_data[6].logic=GPIO_LOW,
    .lcd_data[6].direction=GPIO_DIRECTION_OUTPUT,  
    .lcd_data[7].port=PORD_INDEX,
    .lcd_data[7].pin=PIN7,
    .lcd_data[7].logic=GPIO_LOW,
    .lcd_data[7].direction=GPIO_DIRECTION_OUTPUT 
       
};


void usart_model_init(void){
    
    usart_obj.baudrate=9600;
    usart_obj.baudrate_gen_config =BAUDRATE_ASYN_8BIT_LOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable=EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable=EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;    

    usart_obj.usart_rx_cfg.usart_rx_enable=EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable=EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;  
    
    usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
   
    
}
dc_motor_t dc_motor1= {
  .dc_motor_pin[0].pin= PIN0,
  .dc_motor_pin[0].port=PORC_INDEX,
  .dc_motor_pin[0].direction=DC_MOTOR_OFF_STATUS,
  .dc_motor_pin[1].pin= PIN1,
  .dc_motor_pin[1].port=PORC_INDEX,
  .dc_motor_pin[1].direction=DC_MOTOR_OFF_STATUS
 };
dc_motor_t dc_motor2= {
  .dc_motor_pin[0].pin= PIN2,
  .dc_motor_pin[0].port=PORTA_INDEX,
  .dc_motor_pin[0].logic=GPIO_LOW,
  .dc_motor_pin[0].direction=DC_MOTOR_OFF_STATUS,
  .dc_motor_pin[1].pin= PIN5,
  .dc_motor_pin[1].port=PORC_INDEX,
  .dc_motor_pin[1].logic=GPIO_LOW,
  .dc_motor_pin[1].direction=DC_MOTOR_OFF_STATUS
 };

void CCP1_DefaultInterruptHandler(void) {
    compare_flag++;
    ret=Timer3_Write_value(&timer_obj,0);
    if (1== compare_flag){
      ret=CCP_Compare_Mode_Set_Value(&ccp1_obj ,2400);
      CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH );
    }
    else if(2 == compare_flag){
      ret=CCP_Compare_Mode_Set_Value(&ccp1_obj ,17600);  
      CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW );
      compare_flag=0;
    }
}



void timer3_timer_init(void){
    
    timer_obj.TMR3_InterruptHandler=NULL;
    timer_obj.prescaler_value= TIMER3_PRESCALER_DIV_BY_1;   
    timer_obj.timer3_mode=TIMER3_TIMER_MODE;
    timer_obj.priority=INTERRUPT_LOW_PRIORITY;
    timer_obj.timer3_preload_value=0;
    timer_obj.timer3_reg_rw_mode=TIMER3_RW_REG_8BIT_MODE;
       
    ret=Timer3_Init(&timer_obj);
}

void CCP_SET_Duty(void){
   
    
    ccp1_obj.ccp_inst=CCP1_INST;
    ccp1_obj.CCP1_InterruptHandler=CCP1_DefaultInterruptHandler;
    ccp1_obj.ccp_mode= CCP_COMPARE_MODE_SELECTED;    
    ccp1_obj.ccp_variant= CCP_COMPARE_MODE_SET_PIN_LOW   ;
    ccp1_obj.ccp_capture_timer= CCP1_CCP2_TIMER3;      
    ccp1_obj.ccp_pin.port=PORC_INDEX;
    ccp1_obj.ccp_pin.pin=PIN2;
    ccp1_obj.ccp_pin.direction=GPIO_DIRECTION_OUTPUT;
    
   
}

void ADC_DefaultInterruptHandler(void){
    
     
         
 }

adc_conf_t adc_1={
     .ADC_InterruptHandler=NULL,
     .acquisition_time=ADC_12_TAD,
     .adc_result_format=ADC_RESULT_RIGHT,
     .channel_select=ADC_CHANNEL_AN0,
     .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16,
     .voltage_reference=ADC_VOLTAGE_REFERENCE_DISABLE
 };
  



void ecu_layer_intialize(void){
   
    Std_ReturnType ret= E_NOT_OK;
    usart_model_init();
    ret=dc_motor_initialize(&dc_motor1);
    ret=dc_motor_initialize(&dc_motor2);
    ret=EUSART_ASYNC_Init(&usart_obj);
    ret=lcd_8bit_initialize(&lcd_2);
    ret= ADC_Init(&adc_1);
   
   
}
