/* 
 * File:   hal_ccp1.h
 * Author: Nehal
 *
 * Created on October 24, 2023, 8:09 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "ccp1_cfg.h"
/* Section : Macro Declarations */
#define CCP_MODULE_DISABLE                       ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE          ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE           ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE           ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE          ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW             ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH            ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH         ((uint8)0x02)
#define CCP_COMPARE_GEN_SW_INTERRUPT             ((uint8)0x0A)
#define CCP_COMPARE_GEN_EVENT                    ((uint8)0x0B)
#define CCP_PWM_MODE                             ((uint8)0x0C)

#define CCP_CAPTURE_NOT_READY   0X00
#define CCP_CAPTURE_READY       0X01

#define CCP_COMPARE_NOT_READY   0X00
#define CCP_COMPARE_READY       0X01

/*Timer2 Input Clock Postscaler*/
#define    CCP_TIMER2_POSTSCALER_DIV_BY_1  1
#define    CCP_TIMER2_POSTSCALER_DIV_BY_2  2
#define    CCP_TIMER2_POSTSCALER_DIV_BY_3  3
#define    CCP_TIMER2_POSTSCALER_DIV_BY_4  4
#define    CCP_TIMER2_POSTSCALER_DIV_BY_5  5
#define    CCP_TIMER2_POSTSCALER_DIV_BY_6  6
#define    CCP_TIMER2_POSTSCALER_DIV_BY_7  7
#define    CCP_TIMER2_POSTSCALER_DIV_BY_8  8
#define    CCP_TIMER2_POSTSCALER_DIV_BY_9  9
#define    CCP_TIMER2_POSTSCALER_DIV_BY_10 10
#define    CCP_TIMER2_POSTSCALER_DIV_BY_11 11
#define    CCP_TIMER2_POSTSCALER_DIV_BY_12 12
#define    CCP_TIMER2_POSTSCALER_DIV_BY_13 13
#define    CCP_TIMER2_POSTSCALER_DIV_BY_14 14
#define    CCP_TIMER2_POSTSCALER_DIV_BY_15 15
#define    CCP_TIMER2_POSTSCALER_DIV_BY_16 16 
/*Timer2 Input Clock Prescaler*/
#define    CCP_TIMER2_PRESCALER_DIV_BY_1   1
#define    CCP_TIMER2_PRESCALER_DIV_BY_4  4
#define    CCP_TIMER2_PRESCALER_DIV_BY_16  16
/* Section : Macro Function Declarations */
#define CCP1_SET_MODE(_CONFIG)                (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)                (CCP2CONbits.CCP2M = _CONFIG)
/* Section : Data Type Declarations */
typedef enum {
    CCP_CAPTURE_MODE_SELECTED =0,
    CCP_COMPARE_MODE_SELECTED ,
    CCP_PWM_MODE_SELECTED         
            
}ccp1_mode_t;
typedef enum {
    CCP1_INST = 0,
    CCP2_INST        
}ccp_inst_t ;

typedef enum {
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3      
}ccp_capture_timer_t ;
typedef union {
    struct {
        uint8 ccpr_low ;
        uint8 ccpr_high ;
    };
    
    struct {
        uint16 ccpr_16Bit;  
        
    };
}CCP_REG_T;
typedef struct{
ccp1_mode_t ccp_mode; /*CCP1 main mode*/
uint8 ccp_variant ;   /*CCP1 selected mode variant*/
pin_config_t ccp_pin ;
ccp_inst_t ccp_inst;
ccp_capture_timer_t ccp_capture_timer;
#if CCP1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
void (*CCP1_InterruptHandler)(void);
interrupt_priority_cfg CCP1_priority;
#endif 
#if CCP2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
void (*CCP2_InterruptHandler)(void);
interrupt_priority_cfg CCP2_priority;
#endif 

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
uint32 PWM_Frequency;  /*CCP1 PWM mode frequency*/
uint8 postscaler_value :4;
uint8 prescaler_value :2;
#endif
}ccp_t;

/* Section : Function Declarations */
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP_IsCaptureDataReady(const ccp_t *_ccp_obj ,uint8 *_capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj ,uint16 *capture_value);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED ) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED )
Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj ,uint8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj ,uint16 compare_value);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj,const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif

#endif	/* HAL_CCP1_H */

