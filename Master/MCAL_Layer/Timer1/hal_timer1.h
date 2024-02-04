/* 
 * File:   hal_timer1.h
 * Author: Nehal
 *
 * Created on October 20, 2023, 6:26 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : Includes*/
#include"pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"


/* Section : Macro Declarations */
#define TIMER1_COUNTER_MODE 1
#define TIMER1_TIMER_MODE 0
#define TIMER1_ASNYC_COUNTER_MODE 1
#define TIMER1_SYNC_COUNTER_MODE 0
#define TIMER1_OSCILLATOR_ENABLE 1
#define TIMER1_OSCILLATOR_DISABLE 0
#define TIMER1_RW_REG_16BIT_MODE  1
#define TIMER1_RW_REG_8BIT_MODE  0
/* Section : Macro Function Declarations */

#define TIMER1_TIMER_MODE_ENABLE()                     (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE()                   (T1CONbits.TMR1CS=1)

#define TIMER1_MODULE_ENABLE()                         (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_DISABLE()                        (T1CONbits.TMR1ON=0)

#define TIMER1_ASNYC_COUNTER_MODE_ENABLE()             (T1CONbits.T1SYNC=1) 
#define TIMER1_SNYC_COUNTER_MODE_ENABLE()              (T1CONbits.T1SYNC=0)

#define TIMER1_OSC_ENABLE()                            (T1CONbits.T1OSCEN=1)
#define TIMER1_OSC_DISABE()                            (T1CONbits.T1OSCEN=0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)           (T1CONbits.T1CKPS=_PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()                         (T1CONbits.T1RUN)

#define TIMER1_RW_REG_16BIT_MODE_ENABLE()              (T1CONbits.RD16=1)
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()               (T1CONbits.RD16=0)
/* Section : Data Type Declarations */

typedef enum {
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2 ,
    TIMER1_PRESCALER_DIV_BY_4 ,
    TIMER1_PRESCALER_DIV_BY_8          
                    
}timer1_prescaler_select_t;

typedef struct {
  #if TIMER1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
    void (*TMR1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
  #endif    
   uint16 timer1_preload_value ;
   timer1_prescaler_select_t  prescaler_value ;        
   uint8 timer1_mode : 1 ;
   uint8 timer1_counter_mode : 1 ;
   uint8 timer1_osc_cfg : 1 ;
   uint8 timer1_reg_rw_mode : 1 ;
   uint8 timer1_reserved : 2 ;
   
}timer1_t;
/* Section : Function Declarations */
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_value(const timer1_t *_timer,uint16 _value);
Std_ReturnType Timer1_Read_value(const timer1_t *_timer,uint16 *_value);
#endif	/* HAL_TIMER1_H */

