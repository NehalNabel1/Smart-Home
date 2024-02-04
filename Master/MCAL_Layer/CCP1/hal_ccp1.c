/* 
 * File:   hal_ccp1.h
 * Author: Nehal
 *
 * Created on October 24, 2023, 8:09 PM
 */
#include "hal_ccp1.h"

#if CCP1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*CCP1_Interrupt_Handler)(void)=NULL;
#endif 
#if CCP2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*CCP2_Interrupt_Handler)(void)=NULL;
#endif 
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj);
Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj);
Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj);
void CCP2_ISR(void){
    CCP2_InterruptFlagClear() ;      
    if(CCP2_Interrupt_Handler){
        CCP2_Interrupt_Handler();
    }
    else{/*Nothing*/}
}
void CCP1_ISR(void){
    CCP1_InterruptFlagClear() ;     
    if(CCP1_Interrupt_Handler){
        CCP1_Interrupt_Handler();
    }
    else{/*Nothing*/}
}
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }
    else {
        if( CCP1_INST ==  _ccp_obj->ccp_inst) {
           CCP1_SET_MODE(CCP_MODULE_DISABLE); 
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst) {
           CCP2_SET_MODE(CCP_MODULE_DISABLE); 
        }
        
        if(CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret= CCP_Capture_Mode_Config(_ccp_obj);
        }
        else if(CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret= CCP_Compare_Mode_Config(_ccp_obj);
        } 
        
        else if(CCP_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            #if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
            CCP_PWM_Mode_Config(_ccp_obj);
            #endif 
            
        }
        else {/*Nothing*/}
        /*Pin Configuration */
        ret= gpio_pin_intialize(&(_ccp_obj->ccp_pin));
        /*CCP Interrupt Configuration */
        CCP_Interrupt_Config(_ccp_obj);
        
        
        ret=E_OK;
    }
    
    return ret;   
}
Std_ReturnType CCP1_DeInit(const ccp_t *_ccp_obj){
    Std_ReturnType ret=E_NOT_OK;
    
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }
    else {
        if( CCP1_INST ==  _ccp_obj->ccp_inst) {
           CCP1_SET_MODE(CCP_MODULE_DISABLE); 
           #if CCP1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
           #endif 
        }
        else if( CCP1_INST ==  _ccp_obj->ccp_inst) {
           CCP2_SET_MODE(CCP_MODULE_DISABLE); 
           #if CCP2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
           #endif 
        }     
        
        
        ret=E_OK;
    }
    
    return ret;   
}

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCaptureDataReady(const ccp_t *_ccp_obj ,uint8 *_capture_status){
    Std_ReturnType ret=E_NOT_OK;
    
    if((NULL == _capture_status) || (NULL == _ccp_obj)){
        ret=E_NOT_OK;
    }
    else {
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
            if( CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *_capture_status = CCP_CAPTURE_READY;
                 CCP1_InterruptFlagClear();
            }
            else{
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
            if( CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *_capture_status = CCP_CAPTURE_READY;
                 CCP2_InterruptFlagClear();
            }
            else{
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
            
        }
        
        ret=E_OK;
    }
    
    return ret;   
    
}
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj ,uint16 *capture_value){
    Std_ReturnType ret=E_NOT_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low=0 ,.ccpr_high=0};
    if((NULL == capture_value) || (NULL == _ccp_obj)){
        ret=E_NOT_OK;
    }
    else {
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
            capture_temp_value.ccpr_low = CCPR1L;
            capture_temp_value.ccpr_high=CCPR1H;
            *capture_value = capture_temp_value.ccpr_16Bit;            
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
            capture_temp_value.ccpr_low = CCPR2L;
            capture_temp_value.ccpr_high=CCPR2H;
            *capture_value = capture_temp_value.ccpr_16Bit; 
        
        }
        
        
        ret=E_OK;
    }
    
    return ret;   
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED ) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED )
Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj ,uint8 *_compare_status){
    Std_ReturnType ret=E_NOT_OK;
    
    if((NULL ==_compare_status) || (NULL == _ccp_obj)){
        ret=E_NOT_OK;
    }
    else {
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status =CCP_COMPARE_READY ;
             CCP1_InterruptFlagClear();
            }
            else{
                *_compare_status =  CCP_COMPARE_NOT_READY;
            }   
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
            if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
            *_compare_status =CCP_COMPARE_READY ;
             CCP2_InterruptFlagClear();
            }
            else{
                *_compare_status =  CCP_COMPARE_NOT_READY;
            }   
        }
                    
        
        
        ret=E_OK;
    }
    
    return ret;   
}
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj,uint16 compare_value){
    Std_ReturnType ret=E_NOT_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low=0 ,.ccpr_high=0};
    if (NULL == _ccp_obj){
         ret=E_NOT_OK;
    }
    else{
        
        capture_temp_value.ccpr_16Bit = compare_value;
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;         
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;         
        }
    
    
    ret=E_OK;
    }
    return ret;   
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)    
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj,const uint8 _duty){
     Std_ReturnType ret=E_NOT_OK;
     uint16 l_duty_temp =0;
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }    
    else{
        l_duty_temp = (uint16)(4*(PR2 +1)*( _duty /100.0));   
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
           CCP1CONbits.DC1B= (uint8)(l_duty_temp & 0x0003);
           CCPR1L=(uint8)(l_duty_temp >> 2);
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B= (uint8)(l_duty_temp & 0x0003);
            CCPR2L=(uint8)(l_duty_temp >> 2);
           
        }
        else{/*Nothing*/}
    ret=E_OK;
    }
    return ret;     
    
}

Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }
    
    else{
            
    if( CCP1_INST ==  _ccp_obj->ccp_inst){
       CCP1_SET_MODE(CCP_PWM_MODE);
    }
    else if( CCP2_INST ==  _ccp_obj->ccp_inst){
       CCP2_SET_MODE(CCP_PWM_MODE); 
    }
    else{/*Nothing*/}
   
  
    ret=E_OK;
    }
    return ret;   
}

Std_ReturnType CCP1_PWM1_Stop(const ccp_t *_ccp_obj){
    Std_ReturnType ret=E_NOT_OK;
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }    
    else{
            
        if( CCP1_INST ==  _ccp_obj->ccp_inst){
           CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if( CCP2_INST ==  _ccp_obj->ccp_inst){
           CCP2_SET_MODE(CCP_MODULE_DISABLE); 
        }
        else{/*Nothing*/}
    ret=E_OK;
    }
    return ret;     
}
#endif




static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
/*CCP1 Interrupt Configuration */
#if CCP1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_LowPrioritySet();
        }
        else{}
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        CCP1_Interrupt_Handler=_ccp_obj->CCP1_InterruptHandler;
#endif  
        
        
        /*CCP2 Interrupt Configuration */
#if CCP2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP2_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_LowPrioritySet();
        }
        else{/*Nothing*/}
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        CCP2_Interrupt_Handler=_ccp_obj->CCP2_InterruptHandler;
#endif     
    
}
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj){
    if( CCP1_INST ==  _ccp_obj->ccp_inst){
               if(CCP_PWM_MODE == _ccp_obj->ccp_variant){
                CCP1_SET_MODE(CCP_PWM_MODE); 
                
            }
            else {/*Nothing*/}
            }
            else if( CCP2_INST ==  _ccp_obj->ccp_inst){
              if(CCP_PWM_MODE == _ccp_obj->ccp_variant){
                CCP2_SET_MODE(CCP_PWM_MODE); 
                
            }
            else {/*Nothing*/}
            }
            else{/*Nothing*/}
            /*Initialization PWM frequency*/
             PR2=(uint8)((_XTAL_FREQ/(_ccp_obj->PWM_Frequency *4.0* _ccp_obj->postscaler_value*
                        _ccp_obj->prescaler_value))-1);
    
}
#endif
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj){
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /*Timer3 is the capture/compare clock source for the CCP modules*/ 
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP2=1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /*Timer3 is the capture/compare clock source for CCP2*/
        /*Timer1 is the capture/compare clock source for CCP1*/
        T3CONbits.T3CCP1=1;
        T3CONbits.T3CCP2=0;
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer){
        /*Timer1 is the capture/compare clock source for the CCP modules*/
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP2=0;
    }
    else {/*Nothing*/}
    
}
Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj){
   Std_ReturnType ret=E_OK;
   if( CCP1_INST ==  _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_variant){                
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE( CCP_CAPTURE_MODE_1_FALLING_EDGE );break;
                    case CCP_CAPTURE_MODE_1_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
                    case CCP_CAPTURE_MODE_4_RISING_EDGE : CCP1_SET_MODE( CCP_CAPTURE_MODE_4_RISING_EDGE );break;
                    case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE( CCP_CAPTURE_MODE_16_RISING_EDGE );break;
                    default : ret=E_NOT_OK;
                }
            }
            else if( CCP2_INST ==  _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_variant){
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE( CCP_CAPTURE_MODE_1_FALLING_EDGE );break;
                    case CCP_CAPTURE_MODE_1_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
                    case CCP_CAPTURE_MODE_4_RISING_EDGE : CCP2_SET_MODE( CCP_CAPTURE_MODE_4_RISING_EDGE );break;
                    case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE( CCP_CAPTURE_MODE_16_RISING_EDGE );break;
                    default : ret=E_NOT_OK;
                    
                } 
            }
            CCP_Mode_Timer_Select(_ccp_obj);
   
   return ret;
}

Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj){
   Std_ReturnType ret=E_OK;
   if( CCP1_INST ==  _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_variant){
                    case CCP_COMPARE_MODE_SET_PIN_LOW : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
                    case CCP_COMPARE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_GEN_SW_INTERRUPT);break;
                    case CCP_COMPARE_GEN_EVENT : CCP1_SET_MODE(CCP_COMPARE_GEN_EVENT);break;
                    default : ret=E_NOT_OK;
                }
            } 
            else if( CCP2_INST ==  _ccp_obj->ccp_inst){
                switch(_ccp_obj->ccp_variant){
                    case CCP_COMPARE_MODE_SET_PIN_LOW : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
                    case CCP_COMPARE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_GEN_SW_INTERRUPT);break;
                    case CCP_COMPARE_GEN_EVENT : CCP2_SET_MODE(CCP_COMPARE_GEN_EVENT);break;
                    default : ret=E_NOT_OK;
                }
            }    
            CCP_Mode_Timer_Select(_ccp_obj);
   
   return ret;
}