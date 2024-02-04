/* 
 * File:   hal_i2c.c
 * Author: Nehal
 *
 * Created on November 29, 2023, 6:09 PM
 */
#include"hal_i2c.h"
static inline void MSSP_I2C_MODE_GPIO_CFG(void);
static inline void MSSP_I2C_Master_Mode_Clock_CFG(const mssp_i2c_t *i2c_obj);
static inline void MSSP_I2C_Interrupt_Configuration(const mssp_i2c_t *i2c_obj);
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE  
static void(*I2C_Report_Write_Collision_InterruptHandler)(void)=NULL;
static void(*I2C_DefaultInterruptHandler)(void)=NULL;
static void(*I2C_Report_Receive_Overflow_InterruptHandler)(void)=NULL;
#endif 

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret= E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else {
        /*Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /*MSSP I2C Select Mode*/
        if(MSSP_I2C_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode){/* MSSP I2C Master Mode Configurations */
            /* I2C Master Mode Clock Configurations */
            MSSP_I2C_Master_Mode_Clock_CFG(i2c_obj);
        }
        else if(MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode){/*MSSP I2C Slave Mode Configurations*/
           /*I2C Slave Mode General Call Configurations*/ 
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else{/*Nothing*/}
            /*Clear Write Collision Detect*/
            SSPCON1bits.WCOL=0; /*No Collision*/
            /*Clear The Receive Overflow Indicator*/
            SSPCON1bits.SSPOV=0; /*No Overflow*/
            /*Release the Clock*/
            SSPCON1bits.CKP=1;
            /*Assign The I2C Slave Address*/
            SSPADD=i2c_obj->i2c_cfg.i2c_slave_address;
            /*I2C Slave Mode Configurations*/
            I2C_MODE_SELECT_CFG(i2c_obj->i2c_cfg.i2c_mode_cfg);
        }
        else{/*Nothing*/}                   
        /*I2C Master/Slave Mode GPIO configurations */
        MSSP_I2C_MODE_GPIO_CFG();          
        /*MSSP I2C Slew Rate Control*/
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{/*Nothing*/}
        /*MSSP I2C SMBus Control*/
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_DISABLE_CFG();
        }
        else{/*Nothing*/}
/*Interrupt Configuration*/        
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE       
 MSSP_I2C_Interrupt_Configuration(i2c_obj);
#endif        
        /*Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
        
        ret=E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret= E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else {
        MSSP_MODULE_DISABLE_CFG();
/*Interrupt Configuration*/        
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
        MSSP_I2C_InterruptDisable();
        MSSP_I2C_BUS_COL_InterruptDisable();
#endif        
        ret=E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret= E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else {
        /* Initiates Start condition on SDA and SCL pins */ 
         SSPCON2bits.SEN=1;
        /* Wait for the completion of the Start condition */
         while(SSPCON2bits.SEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
         PIR1bits.SSPIF=0;
        /* Report the Start condition Detection */
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            ret=E_OK;
        }
        else{
            ret=E_NOT_OK;
        }       
        
       
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret= E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else {     

        /* Initiates Repeated Start condition on SDA and SCL pins */ 
         SSPCON2bits.RSEN=1;
        /* Wait for the completion of the Repeated Start condition */
         while(SSPCON2bits.RSEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
         PIR1bits.SSPIF=0;
        
        ret=E_OK;
            
        
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret= E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else {
        /* Initiates Stop condition on SDA and SCL pins */ 
         SSPCON2bits.PEN=1;
        /* Wait for the completion of the Stop condition */
         while(SSPCON2bits.PEN);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
         PIR1bits.SSPIF=0;
        /* Report the Stop condition Detection */
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
            ret=E_OK;
        }
        else{
            ret=E_NOT_OK;
        }       
        
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj ,uint8 i2c_data ,uint8 *ack){
    Std_ReturnType ret= E_NOT_OK;
    
    if((NULL == i2c_obj) || (NULL == ack)){
        ret=E_NOT_OK;
    }
    else {
        /* Write Data to the Data register */ 
        SSPBUF=i2c_data;    
        /* Wait The transmission to be completed */
        while(!PIR1bits.SSPIF);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF=0;
        /* Report the acknowledge received from the slave */
        if(I2C_MASTER_RECEIVE_ACK_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *ack = I2C_MASTER_RECEIVE_ACK_FROM_SLAVE;
        }
        else{
           *ack = I2C_MASTER_NOT_RECEIVE_ACK_FROM_SLAVE; 
        }
        ret=E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj ,uint8 ack ,uint8 *i2c_data){
    Std_ReturnType ret= E_NOT_OK;
    
    if((NULL == i2c_obj) || (NULL == i2c_data)){
        ret=E_NOT_OK;
    }
    else {
        /*Master Mode Receive Enable*/
        I2C_MASTER_RECEIVE_MODE_ENABLE_CFG();
        /*Wait for Buffer Full Flag : A complete byte received*/
        while(!SSPSTATbits.BF);
        *i2c_data=SSPBUF;
        /*Send ACK or NACK After Read*/
        if(I2C_MASTER_SEND_ACK == ack){
             SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
             /*Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit*/
             SSPCON2bits.ACKEN=1;
        }
        else if(I2C_MASTER_SEND_NACK == ack){
             SSPCON2bits.ACKDT = I2C_MASTER_SEND_NACK; 
             /*Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit*/
             SSPCON2bits.ACKEN=1;            
        }
        else{/*Nothing*/}
            
        
        ret=E_OK;
    }
    return ret;
}
static inline void MSSP_I2C_MODE_GPIO_CFG(void){
    TRISCbits.TRISC3=1; /*Serial clock (SCL) Input*/
    TRISCbits.TRISC4=1; /*Serial data (SDA) Input*/
}
static inline void MSSP_I2C_Master_Mode_Clock_CFG(const mssp_i2c_t *i2c_obj){
    I2C_MODE_SELECT_CFG(i2c_obj->i2c_cfg.i2c_mode_cfg);
    SSPADD= (uint8)(((_XTAL_FREQ/4.0)/i2c_obj->i2c_clock) - 1);
}

static inline void MSSP_I2C_Interrupt_Configuration(const mssp_i2c_t *i2c_obj){
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    MSSP_I2C_InterruptEnable() ;
        MSSP_I2C_BUS_COL_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        MSSP_I2C_BUS_COL_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY ==i2c_obj->i2c_cfg.MSSP_I2C_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.MSSP_I2C_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_LowPrioritySet(); 
        }
        else{/*Nothing*/}
        
        if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.MSSP_I2C_bus_col_priority){
            INTERRUPT_GlobalInterruptHighEnable();
             MSSP_I2C_BUS_COL_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.MSSP_I2C_bus_col_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_BUS_COL_LowPrioritySet();
        }
        else{/*Nothing*/}
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        I2C_Report_Write_Collision_InterruptHandler=i2c_obj->I2C_Report_Write_Collision;
        I2C_DefaultInterruptHandler=i2c_obj->I2C_DefaultInterruptHandler;
        I2C_Report_Receive_Overflow_InterruptHandler=i2c_obj->I2C_Report_Receive_Overflow;
        
#endif          
    
}

void MSSP_I2C_ISR(void){  
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_InterruptFlagClear();
    if(I2C_DefaultInterruptHandler){
        I2C_DefaultInterruptHandler();
    }
    else{/*Nothing*/}
#endif
}
void MSSP_I2C_BC_ISR(void){   
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(I2C_Report_Write_Collision_InterruptHandler){
        I2C_Report_Write_Collision_InterruptHandler();
    }
    else{/*Nothing*/}
#endif    
}

uint8 I2C_Read_Register(const mssp_i2c_t *i2c_obj ,uint8 _Address,uint8 reg_address){
    uint8 read_Value ;   
    uint8 slave_ack;
  Std_ReturnType ret= E_NOT_OK;
   ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,_Address,&slave_ack);
    __delay_ms(10)   ;
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,reg_address,&slave_ack);
    __delay_ms(10)   ;
      ret=MSSP_I2C_Master_Send_Repeated_Start(&i2c_obj); 
    __delay_ms(10)   ; 
      ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,(_Address+1),&slave_ack);    
    __delay_ms(10)   ;        
    ret=MSSP_I2C_Master_Read_Blocking(&i2c_obj,I2C_MASTER_SEND_NACK,&read_Value);
    __delay_ms(10)   ; 
     ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ;   
    
    
    return read_Value;
}
Std_ReturnType I2C_Write_Register(const mssp_i2c_t *i2c_obj,uint8 _Address,uint8 reg_address ,uint8 i2c_data){
     Std_ReturnType ret= E_NOT_OK;
       
    uint8 slave_ack;
  ret= MSSP_I2C_Master_Send_Start(&i2c_obj); 
    __delay_ms(10)   ;
     ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,_Address,&slave_ack);
    __delay_ms(10)   ;     
    ret= MSSP_I2C_Master_Write_Blocking(&i2c_obj,i2c_data,&slave_ack);    
    __delay_ms(10)   ; 
     ret= MSSP_I2C_Master_Send_Stop(&i2c_obj);
    __delay_ms(10)   ;   
    
    ret=E_OK;   
    return ret;
    
}

