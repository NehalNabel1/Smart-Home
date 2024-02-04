/* 
 * File:   hal_i2c.h
 * Author: Nehal
 *
 * Created on November 29, 2023, 6:09 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */

/*Slew Rate Control bit*/
#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE 0
/*SMBus Select bit*/
#define I2C_SMBus_ENABLE 1
#define I2C_SMBus_DISABLE 0
/*Slave Mode Indicates that the last byte data/address*/
#define I2C_LAST_BYTE_DATA 1
#define I2C_LAST_BYTE_ADDRESS 0
/*Stop Condition Indication*/
#define I2C_STOP_BIT_DETECTED 1
#define I2C_STOP_BIT_NOT_DETECTED 0
/*Start Condition Indication*/
#define I2C_START_BIT_DETECTED 1
#define I2C_START_BIT_NOT_DETECTED 0
/*Master/Slave Mode*/
#define MSSP_I2C_MASTER_MODE  1
#define MSSP_I2C_SLAVE_MODE  0

/* Master Synchronous Serial Port Mode Select*/
#define I2C_SLAVE_MODE_7BIT_ADDRESS                      0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                     0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE        0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE       0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK                    0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED              0x0BU
/*General Call Enable bit (Slave mode only)*/
#define I2C_GENERAL_CALL_ENABLE  1
#define I2C_GENERAL_CALL_DISABLE  0
/* Master Receive Mode Enable/Disable */
#define I2C_MASTER_RECEIVE_MODE_ENABLE  1
#define I2C_MASTER_RECEIVE_MODE_DISABLE  0
/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_MASTER_RECEIVE_ACK_FROM_SLAVE   0
#define I2C_MASTER_NOT_RECEIVE_ACK_FROM_SLAVE  1
/*  Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK   0
#define I2C_MASTER_SEND_NACK   1

/* Section : Macro Function Declarations */

#define I2C_SLEW_RATE_DISABLE_CFG()                  (SSPSTATbits.SMP=1)
#define I2C_SLEW_RATE_ENABLE_CFG()                   (SSPSTATbits.SMP=0)
/*SMBus Select bit*/
#define I2C_SMBus_ENABLE_CFG()                       (SSPSTATbits.CKE=1)   
#define I2C_SMBus_DISABLE_CFG()                      (SSPSTATbits.CKE=0)
/*General Call Enable bit (Slave mode only)*/
#define I2C_GENERAL_CALL_ENABLE_CFG()                (SSPCON2bits.GCEN=1)
#define I2C_GENERAL_CALL_DISABLE_CFG()               (SSPCON2bits.GCEN=0)
/* Master Receive Mode Enable/Disable */
#define I2C_MASTER_RECEIVE_MODE_ENABLE_CFG()         (SSPCON2bits.RCEN=1)
#define I2C_MASTER_RECEIVE_MODE_DISABLE_CFG()        (SSPCON2bits.RCEN=0)
/*Master Synchronous Serial Port Enable bit(*/
#define MSSP_MODULE_ENABLE_CFG()                     (SSPCON1bits.SSPEN=1)
#define MSSP_MODULE_DISABLE_CFG()                    (SSPCON1bits.SSPEN=0)
/*I2C Master Mode Clock Configurations*/
#define I2C_MODE_SELECT_CFG(_mode)                   (SSPCON1bits.SSPM=_mode)
/* SCK Release Control bit*/
#define I2C_CLOCK_STRETCH_ENABLE()                   (SSPCON1bits.CKP=0)
#define I2C_CLOCK_STRETCH_DISABLE()                  (SSPCON1bits.CKP=1)

/* Section : Data Type Declarations */
typedef struct{
    uint8 i2c_mode_cfg  ;
    uint8 i2c_slave_address;
    uint8 i2c_mode : 1 ; /*Master or Slave*/
    uint8 i2c_slew_rate : 1;
    uint8 i2c_SMBus_control : 1;
    uint8 i2c_general_call : 1 ;
    uint8 i2c_master_rec_mode : 1; /* Master Receive Mode Enable/Disable */
    uint8 i2c_reserved : 3 ;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
   interrupt_priority_cfg MSSP_I2C_priority;
   interrupt_priority_cfg MSSP_I2C_bus_col_priority;
#endif   
    
}i2c_configs_t;
typedef struct{
    uint32 i2c_clock ;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    void (*I2C_DefaultInterruptHandler)(void);
    void (*I2C_Report_Write_Collision)(void);
    void (*I2C_Report_Receive_Overflow)(void);
#endif        
    
    i2c_configs_t i2c_cfg;
}mssp_i2c_t;
/* Section : Function Declarations */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj ,uint8 i2c_data ,uint8 *ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj ,uint8 ack ,uint8 *i2c_data);
uint8 I2C_Read_Register(const mssp_i2c_t *i2c_obj,uint8 _Address,uint8 reg_address);
Std_ReturnType I2C_Write_Register(const mssp_i2c_t *i2c_obj,uint8 _Address,uint8 reg_address ,uint8 i2c_data);

#endif	/* HAL_I2C_H */

