/* 
 * File:   hal_timer2.c
 * Author: Nehal
 *
 * Created on October 21, 2023, 9:28 PM
 */

#include "hal_timer2.h"
#if TIMER2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*TMR2_Interrupt_Handler)(void)=NULL;
#endif 
static uint8 timer2_preload = ZERO_INIT ;

Std_ReturnType Timer2_Init(const timer2_t *_timer){
     Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer){
        ret=E_NOT_OK;
    }
    else {
        
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer->prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->postscaler_value);
        TMR2=_timer->timer2_preload_value ;
        
        timer2_preload = _timer->timer2_preload_value;
        
        /*Interrupt Configuration*/
        #if TIMER2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        }
        else{/*Nothing*/}
        #else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TMR2_Interrupt_Handler=_timer->TMR2_InterruptHandler;
        #endif  
        TIMER2_MODULE_ENABLE() ;
        
        
        
        ret=E_OK;
    }
    
    return ret;
}
Std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer){
        ret=E_NOT_OK;
    }
    else {
        TIMER2_MODULE_DISABLE() ;        
        #if TIMER2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
        #endif 
        
        
        ret=E_OK;
    }
    
    return ret;
}
Std_ReturnType Timer2_Write_value(const timer2_t *_timer,uint8 _value){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _timer){
        ret=E_NOT_OK;
    }
    else {
        TMR2=_value;
        
        ret=E_OK;
    }
    
    return ret;
}
Std_ReturnType Timer2_Read_value(const timer2_t *_timer,uint8 *_value){
    Std_ReturnType ret=E_NOT_OK;
    
    if((NULL == _timer) || (NULL == _value)){
        ret=E_NOT_OK;
    }
    else {
        *_value=TMR2;
        
        ret=E_OK;
    }
    
    return ret;
}

void TMR2_ISR(void){
    TIMER2_InterruptFlagClear() ;
    TMR2=timer2_preload;    
    if(TMR2_Interrupt_Handler){
        TMR2_Interrupt_Handler();
    }
    else{/*Nothing*/}
}