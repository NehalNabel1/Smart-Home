/* 
 * File:   ecu_layer_init.c
 * Author: Nehal
 *
 * Created on September 4, 2023, 10:21 PM
 */
#include "ecu_layer_init.h"

mssp_i2c_t i2c_obj;
usart_t usart_obj;
timer3_t timer_obj;
timer1_t timer1_obj;
ccp_t ccp1_obj;
ccp_t ccp2_obj;
volatile uint8 compare_flag=0;
volatile uint8 compare2_flag=0;
Std_ReturnType ret= E_NOT_OK;
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
    .lcd_rs.port=PORTA_INDEX,
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

static void I2C_Obj_CFG(void){    
    
    i2c_obj.i2c_clock=100000;
    i2c_obj.i2c_cfg.i2c_mode=MSSP_I2C_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cfg=I2C_MASTER_MODE_DEFINED_CLOCK;
    i2c_obj.i2c_cfg.i2c_SMBus_control=I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    
}
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
keypad_t keypad1={
   .keypad_row_pins[0].port= PORTA_INDEX,
   .keypad_row_pins[0].pin=PIN2,
   .keypad_row_pins[0].logic=GPIO_LOW,
   .keypad_row_pins[0].direction=GPIO_DIRECTION_OUTPUT,
   
   .keypad_row_pins[1].port= PORC_INDEX,
   .keypad_row_pins[1].pin=PIN0,
   .keypad_row_pins[1].logic=GPIO_LOW,
   .keypad_row_pins[1].direction=GPIO_DIRECTION_OUTPUT,
   
   .keypad_row_pins[2].port= PORB_INDEX,
   .keypad_row_pins[2].pin=PIN6,
   .keypad_row_pins[2].logic=GPIO_LOW,
   .keypad_row_pins[2].direction=GPIO_DIRECTION_OUTPUT,
   
   .keypad_row_pins[3].port= PORB_INDEX,
   .keypad_row_pins[3].pin=PIN7,
   .keypad_row_pins[3].logic=GPIO_LOW,
   .keypad_row_pins[3].direction=GPIO_DIRECTION_OUTPUT,
   
   .keypad_coulmn_pins[0].port=PORB_INDEX,
   .keypad_coulmn_pins[0].pin=PIN2,
   .keypad_coulmn_pins[0].logic=GPIO_LOW,
   .keypad_coulmn_pins[0].direction=GPIO_DIRECTION_INPUT,
   
   .keypad_coulmn_pins[1].port=PORB_INDEX,
   .keypad_coulmn_pins[1].pin=PIN3,
   .keypad_coulmn_pins[1].logic=GPIO_LOW,
   .keypad_coulmn_pins[1].direction=GPIO_DIRECTION_INPUT,
   
   .keypad_coulmn_pins[2].port=PORB_INDEX,
   .keypad_coulmn_pins[2].pin=PIN4,
   .keypad_coulmn_pins[2].logic=GPIO_LOW,
   .keypad_coulmn_pins[2].direction=GPIO_DIRECTION_INPUT,
   
   .keypad_coulmn_pins[3].port=PORB_INDEX,
   .keypad_coulmn_pins[3].pin=PIN1,
   .keypad_coulmn_pins[3].logic=GPIO_LOW,
   .keypad_coulmn_pins[3].direction=GPIO_DIRECTION_INPUT,
   
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
void CCP2_DefaultInterruptHandler(void) {
    compare2_flag++;
    ret=Timer3_Write_value(&timer_obj,0);
    if (1== compare2_flag){
      ret=CCP_Compare_Mode_Set_Value(&ccp2_obj ,2400);
      CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH );
    }
    else if(2 == compare2_flag){
      ret=CCP_Compare_Mode_Set_Value(&ccp2_obj ,17600);  
      CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW );
      compare2_flag=0;
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

void timer1_timer_init(void){
    
    timer1_obj.TMR1_InterruptHandler=NULL;
    timer1_obj.prescaler_value= TIMER1_PRESCALER_DIV_BY_1;   
    timer1_obj.timer1_mode=TIMER3_TIMER_MODE;
    timer1_obj.priority=INTERRUPT_HIGH_PRIORITY;
    timer1_obj.timer1_preload_value=0;
    timer1_obj.timer1_reg_rw_mode=TIMER1_RW_REG_8BIT_MODE;
       
    ret=Timer1_Init(&timer1_obj);
}
void CCP1_SET_Duty(void){
   
    
    ccp1_obj.ccp_inst=CCP1_INST;
    ccp1_obj.CCP1_InterruptHandler=CCP1_DefaultInterruptHandler;
    ccp1_obj.ccp_mode= CCP_COMPARE_MODE_SELECTED;    
    ccp1_obj.ccp_variant= CCP_COMPARE_MODE_SET_PIN_LOW   ;
    ccp1_obj.ccp_capture_timer= CCP1_TIMER1_CCP2_TIMER3;      
    ccp1_obj.ccp_pin.port=PORC_INDEX;
    ccp1_obj.ccp_pin.pin=PIN2;
    ccp1_obj.ccp_pin.direction=GPIO_DIRECTION_OUTPUT;
    
    
   
}
void CCP2_SET_Duty(void){
   
    
    ccp2_obj.ccp_inst=CCP2_INST;
    ccp2_obj.CCP2_InterruptHandler=CCP2_DefaultInterruptHandler;
    ccp2_obj.ccp_mode= CCP_COMPARE_MODE_SELECTED;    
    ccp2_obj.ccp_variant= CCP_COMPARE_MODE_SET_PIN_LOW   ;
    ccp2_obj.ccp_capture_timer= CCP1_TIMER1_CCP2_TIMER3;      
    ccp2_obj.ccp_pin.port=PORC_INDEX;
    ccp2_obj.ccp_pin.pin=PIN1;
    ccp2_obj.ccp_pin.direction=GPIO_DIRECTION_OUTPUT;
    
    
   
}
relay_t relay1={
   .relay_pin= PIN3,
   .relay_port=PORTA_INDEX,
   .relay_status=RELAY_OFF_STATUS
};
relay_t relay2={
   .relay_pin= PIN5,
   .relay_port=PORTA_INDEX,
   .relay_status=RELAY_OFF_STATUS
};
led_t led1={.port_name=PORB_INDEX, .pin=PIN0, .led_status=GPIO_LOW};
led_t led2={.port_name=PORB_INDEX, .pin=PIN5, .led_status=GPIO_LOW};




void ecu_layer_intialize(void){
   
    Std_ReturnType ret= E_NOT_OK;
    I2C_Obj_CFG();
    ret=MSSP_I2C_Init(&i2c_obj);
    usart_model_init();
    ret=EUSART_ASYNC_Init(&usart_obj);
    ret=lcd_8bit_initialize(&lcd_2);
    ret=keypad_initialize(&keypad1);
    ret=relay_initialize(&relay1);
    ret=relay_initialize(&relay2);
    ret=led_initialize(&led1);
    ret=led_initialize(&led2);
    
   
}
void Door1_Open(void){
    CCP1_SET_Duty();
    ret=CCP_Compare_Mode_Set_Value(&ccp1_obj ,17600);    
    ret= CCP_Init(&ccp1_obj);   
    timer1_timer_init();
    
}
void Door2_Open(void){
    CCP2_SET_Duty();
    ret=CCP_Compare_Mode_Set_Value(&ccp2_obj ,17600);
    ret= CCP_Init(&ccp2_obj);   
    timer3_timer_init();
    
}
