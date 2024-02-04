/* 
 * File:   mcal_external_interrupt.c
 * Author: Nehal
 *
 * Created on September 15, 2023, 2:44 PM
 */
#include "mcal_external_interrupt.h"
/*Pointer to function hold the callbacks for INTx*/
InterruptHandler INT0_InterruptHandler = NULL;
InterruptHandler INT1_InterruptHandler = NULL;
InterruptHandler INT2_InterruptHandler = NULL;
/*Pointer to function hold the callbacks for RBx*/
InterruptHandler RB4_InterruptHandler_HIGH = NULL;
InterruptHandler RB4_InterruptHandler_LOW = NULL;
InterruptHandler RB5_InterruptHandler_HIGH = NULL;
InterruptHandler RB5_InterruptHandler_LOW = NULL;
InterruptHandler RB6_InterruptHandler_HIGH = NULL;
InterruptHandler RB6_InterruptHandler_LOW = NULL;
InterruptHandler RB7_InterruptHandler_HIGH = NULL;
InterruptHandler RB7_InterruptHandler_LOW = NULL;



static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);


void INT0_ISR(){
    /* INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear() ;
    /* code */
    
    /* Callback function gets call every time this ISR execute */
    if(INT0_InterruptHandler){ INT0_InterruptHandler();}
    else {/*Nothing*/}
}

void INT1_ISR(){
    /* INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear() ;
    /* code */
    
    /* Callback function gets call every time this ISR execute */
    if(INT1_InterruptHandler){ INT1_InterruptHandler();}
    else {/*Nothing*/}
}

void INT2_ISR(){
    /* INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear() ;
    /* code */
    
    /* Callback function gets call every time this ISR execute */
    if(INT2_InterruptHandler){ INT2_InterruptHandler();}
    else {/*Nothing*/}
}
/*========================================= PortB External On Change Start========================================*/
void RB4_ISR(uint8 RB4_source){
    /* RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear() ;
    /* code */
    if (0 == RB4_source){
        /* Callback function gets call every time this ISR execute */
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH();}
        else {/*Nothing*/}
    }  
    else if(1 == RB4_source){
        /* Callback function gets call every time this ISR execute */
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW();}
        else {/*Nothing*/}
    }
    else {/*Nothing*/}
    
}

void RB5_ISR(uint8 RB5_source){
    /* RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear() ;
    /* code */
    if (0 == RB5_source){
        /* Callback function gets call every time this ISR execute */
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH();}
        else {/*Nothing*/}
    }  
    else if(1 == RB5_source){
        /* Callback function gets call every time this ISR execute */
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW();}
        else {/*Nothing*/}
    }
    else {/*Nothing*/}
    
}

void RB6_ISR(uint8 RB6_source){
    /* RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear() ;
    /* code */
    if (0 == RB6_source){
        /* Callback function gets call every time this ISR execute */
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH();}
        else {/*Nothing*/}
    }  
    else if(1 == RB6_source){
        /* Callback function gets call every time this ISR execute */
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW();}
        else {/*Nothing*/}
    }
    else {/*Nothing*/}
    
}

void RB7_ISR(uint8 RB7_source){
    /* RB7 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear() ;
    /* code */
    if (0 == RB7_source){
        /* Callback function gets call every time this ISR execute */
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH();}
        else {/*Nothing*/}
    }  
    else if(1 == RB7_source){
        /* Callback function gets call every time this ISR execute */
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW();}
        else {/*Nothing*/}
    }
    else {/*Nothing*/}
    
}



/*========================================= PortB External On Change End========================================*/


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {
        /*Disable the External interrupt*/
        ret|=Interrupt_INTx_Disable(int_obj);
        /*Clear interrupt flag*/
        ret|=Interrupt_INTx_Clear_Flag(int_obj);
        /*Configure External interrupt edge*/
        ret|=Interrupt_INTx_Edge_Init(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /*Configure External interrupt priority*/
        ret|=Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /*Configure External interrupt I/O pin*/
        ret|Interrupt_INTx_Pin_Init(int_obj);
        /*Configure Default interrupt CallBack*/  
        ret|=Interrupt_INTx_SetInterruptHandler(int_obj);
        /*Enable the External interrupt*/
        ret|=Interrupt_INTx_Enable(int_obj);
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {       
        ret= Interrupt_INTx_Disable(int_obj);
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t*int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {       
        /*This routine clears the interrupt enable for the external interrupt ,RBx*/        
        ret|=Interrupt_RBx_Disable(int_obj);
        /*This routine clears the interrupt flag for the external interrupt ,RBx*/
        ret|=Interrupt_RBx_Clear_Flag(int_obj);    
        /*Configure External interrupt priority*/
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret|=Interrupt_RBx_Priority_Init(int_obj)  ;
        #endif              
        /*Initialize RBx to be input*/
        ret|=Interrupt_RBx_Pin_Init(int_obj);
        /*Initialize call back functions*/
        ret|=Interrupt_RBx_SetInterruptHandler (int_obj) ;      
        /*This routine sets the interrupt enable for the external interrupt ,RBx*/
        ret|=Interrupt_RBx_Enable(int_obj);
        
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {   
        ret= Interrupt_RBx_Disable(int_obj);
                
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {     
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();    
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                                  
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
               
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
            default: ret=E_NOT_OK;
        }
       
        
        }
    
    return ret;   
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {   
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: EXT_INT0_InterruptDisable() ;break;
            case INTERRUPT_EXTERNAL_INT1: EXT_INT1_InterruptDisable() ;break;
            case INTERRUPT_EXTERNAL_INT2: EXT_INT2_InterruptDisable() ;break;
            default: ret=E_NOT_OK;
        }
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {
        
         switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT1: 
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet();}
                else{/*Nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet();}
                else{/*Nothing*/}
                break;
            default: ret=E_NOT_OK;
        }
        
        }
    
    return ret;   
    
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {     
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                else{/*Nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                else{/*Nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                else{/*Nothing*/}
                break;
            default: ret=E_NOT_OK;
        }
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {      
        ret=gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {   
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: EXT_INT0_InterruptFlagClear()  ;break;
            case INTERRUPT_EXTERNAL_INT1: EXT_INT1_InterruptFlagClear()  ;break;
            case INTERRUPT_EXTERNAL_INT2: EXT_INT2_InterruptFlagClear()  ;break;
            default: ret=E_NOT_OK;
        }
        
        }
    
    return ret;   
    
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT0_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT1_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    return ret;
    
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT2_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    return ret;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else {   
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT1: INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT2: INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            default: ret=E_NOT_OK;
        }
        
        }
    
    return ret;   
    
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    
        #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
        #endif
        EXT_RBx_InterruptEnable()  ;
    } 
     return ret;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        /*This routine clears the interrupt enable for the external interrupt ,RBx*/
        EXT_RBx_InterruptDisable()   ;
        /*This routine clears the interrupt flag for the external interrupt ,RBx*/
        EXT_RBx_InterruptFlagClear();
        
    } 
     return ret;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        EXT_RBx_InterruptFlagClear(); 
        
    } 
     return ret;
    
    
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    /*This routine set the RBx external interrupt priority to be low priority */
                    EXT_RBx_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    /*This routine set the RBx external interrupt priority to be high priority */
                    EXT_RBx_HighPrioritySet();
                }
                else{/*Nothing*/}
        
    } 
     return ret;
    
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    } 
     return ret;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(NULL == int_obj){
        ret=E_NOT_OK;
    }
    else{
        switch(int_obj->mcu_pin.pin){
                    
                    case PIN4:
                        RB4_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                        RB4_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                        break;
                    case PIN5:
                        RB5_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                        RB5_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                        break;    
                    case PIN6:
                        RB6_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                        RB6_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                        break;   
                    case PIN7:
                        RB7_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                        RB7_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                        break;   
                    default:
                        ret=E_NOT_OK;
                }
    }
    return ret;
    
}
