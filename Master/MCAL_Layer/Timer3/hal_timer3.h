/* 
 * File:   hal_timer3.h
 * Author: Nehal
 *
 * Created on October 21, 2023, 9:35 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"


/* Section : Macro Declarations */
#define TIMER3_COUNTER_MODE 1
#define TIMER3_TIMER_MODE 0
#define TIMER3_ASNYC_COUNTER_MODE 1
#define TIMER3_SYNC_COUNTER_MODE 0
#define TIMER3_RW_REG_16BIT_MODE  1
#define TIMER3_RW_REG_8BIT_MODE  0
/* Section : Macro Function Declarations */

#define TIMER3_TIMER_MODE_ENABLE()                     (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE_ENABLE()                   (T3CONbits.TMR3CS=1)

#define TIMER3_MODULE_ENABLE()                         (T3CONbits.TMR3ON=1)
#define TIMER3_MODULE_DISABLE()                        (T3CONbits.TMR3ON=0)

#define TIMER3_ASNYC_COUNTER_MODE_ENABLE()             (T3CONbits.T3SYNC=1) 
#define TIMER3_SNYC_COUNTER_MODE_ENABLE()              (T3CONbits.T3SYNC=0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_)           (T3CONbits.T3CKPS=_PRESCALER_)

#define TIMER3_RW_REG_16BIT_MODE_ENABLE()              (T3CONbits.RD16=1)
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()               (T3CONbits.RD16=0)

/* Section : Data Type Declarations */
typedef enum {
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2 ,
    TIMER3_PRESCALER_DIV_BY_4 ,
    TIMER3_PRESCALER_DIV_BY_8          
                    
}timer3_prescaler_select_t;

typedef struct {
  #if TIMER3_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
    void (*TMR3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
  #endif    
   uint16 timer3_preload_value ;
   timer3_prescaler_select_t  prescaler_value ;        
   uint8 timer3_mode : 1 ;
   uint8 timer3_counter_mode : 1 ;   
   uint8 timer3_reg_rw_mode : 1 ;
   uint8 timer3_reserved : 5 ;
   
}timer3_t;

/* Section : Function Declarations */
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_value(const timer3_t *_timer,uint16 _value);
Std_ReturnType Timer3_Read_value(const timer3_t *_timer,uint16 *_value);

#endif	/* HAL_TIMER3_H */

