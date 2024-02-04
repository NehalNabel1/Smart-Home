/* 
 * File:   mcal_internal_interrupt.h
 * Author: Nehal
 *
 * Created on September 15, 2023, 2:38 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes*/
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */
#if  ADC_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the ADC Module*/
#define ADC_InterruptDisable()           (PIE1bits.ADIE=0)
/*This routine sets the interrupt enable for the ADC Module*/
#define ADC_InterruptEnable()            (PIE1bits.ADIE=1)
/*This routine clears the interrupt flag for the ADC Module*/
#define ADC_InterruptFlagClear()         (PIR1bits.ADIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the ADC Module priority to be high priority */
#define ADC_HighPrioritySet()            (IPR1bits.ADIP=1)
/*This routine set the ADC Module priority to be low priority */
#define ADC_LowPrioritySet()             (IPR1bits.ADIP=0)

#endif

#endif  

/********************************TIMER0 START*********************************************/
#if TIMER0_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the TIMER0 Module*/
#define TIMER0_InterruptDisable()           (INTCONbits.TMR0IE =0)
/*This routine sets the interrupt enable for the TIMER0 Module*/
#define TIMER0_InterruptEnable()            (INTCONbits.TMR0IE =1)
/*This routine clears the interrupt flag for the TIMER0 Module*/
#define TIMER0_InterruptFlagClear()         (INTCONbits.TMR0IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the TIMER0 Module priority to be high priority */
#define TIMER0_HighPrioritySet()            (INTCON2bits.TMR0IP=1)
/*This routine set the TIMER0 Module priority to be low priority */
#define TIMER0_LowPrioritySet()             (INTCON2bits.TMR0IP =0)
#endif
#endif  
/********************************TIMER0 END***********************************************/

/********************************TIMER1 START**********************************************/
#if TIMER1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the TIMER1 Module*/
#define TIMER1_InterruptDisable()           (PIE1bits.TMR1IE=0)
/*This routine sets the interrupt enable for the TIMER1 Module*/
#define TIMER1_InterruptEnable()            (PIE1bits.TMR1IE=1)
/*This routine clears the interrupt flag for the TIMER1 Module*/
#define TIMER1_InterruptFlagClear()         (PIR1bits.TMR1IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the TIMER1 Module priority to be high priority */
#define TIMER1_HighPrioritySet()            (IPR1bits.TMR1IP=1)
/*This routine set the TIMER1 Module priority to be low priority */
#define TIMER1_LowPrioritySet()             (IPR1bits.TMR1IP=0)
#endif
#endif  

/********************************TIMER1 END**********************************************/

/********************************TIMER2 START**********************************************/
#if TIMER2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the TIMER2 Module*/
#define TIMER2_InterruptDisable()           (PIE1bits.TMR2IE=0)
/*This routine sets the interrupt enable for the TIMER2 Module*/
#define TIMER2_InterruptEnable()            (PIE1bits.TMR2IE=1)
/*This routine clears the interrupt flag for the TIMER2 Module*/
#define TIMER2_InterruptFlagClear()         (PIR1bits.TMR2IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the TIMER2 Module priority to be high priority */
#define TIMER2_HighPrioritySet()            (IPR1bits.TMR2IP=1)
/*This routine set the TIMER2 Module priority to be low priority */
#define TIMER2_LowPrioritySet()             (IPR1bits.TMR2IP=0)
#endif
#endif  

/********************************TIMER2 END**********************************************/

/********************************TIMER3 START**********************************************/
#if TIMER3_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the TIMER3 Module*/
#define TIMER3_InterruptDisable()           (PIE2bits.TMR3IE=0)
/*This routine sets the interrupt enable for the TIMER3 Module*/
#define TIMER3_InterruptEnable()            (PIE2bits.TMR3IE=1)
/*This routine clears the interrupt flag for the TIMER3 Module*/
#define TIMER3_InterruptFlagClear()         (PIR2bits.TMR3IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the TIMER3 Module priority to be high priority */
#define TIMER3_HighPrioritySet()            (IPR2bits.TMR3IP=1)
/*This routine set the TIMER3 Module priority to be low priority */
#define TIMER3_LowPrioritySet()             (IPR2bits.TMR3IP=0)
#endif
#endif  

/********************************TIMER3 END**********************************************/

/********************************CCP1 START**********************************************/
#if CCP1_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the CCP1 Module*/
#define CCP1_InterruptDisable()           (PIE1bits.CCP1IE=0)
/*This routine sets the interrupt enable for the CCP1 Module*/
#define CCP1_InterruptEnable()            (PIE1bits.CCP1IE=1)
/*This routine clears the interrupt flag for the CCP1 Module*/
#define CCP1_InterruptFlagClear()         (PIR1bits.CCP1IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the CCP1 Module priority to be high priority */
#define CCP1_HighPrioritySet()            (IPR1bits.CCP1IP =1)
/*This routine set the CCP1 Module priority to be low priority */
#define CCP1_LowPrioritySet()             (IPR1bits.CCP1IP =0)
#endif
#endif  

/********************************CCP1 END**********************************************/

/********************************CCP2 START**********************************************/
#if CCP2_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the CCP2 Module*/
#define CCP2_InterruptDisable()           (PIE2bits.CCP2IE=0)
/*This routine sets the interrupt enable for the CCP2 Module*/
#define CCP2_InterruptEnable()            (PIE2bits.CCP2IE=1)
/*This routine clears the interrupt flag for the CCP2 Module*/
#define CCP2_InterruptFlagClear()         (PIR2bits.CCP2IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the CCP2 Module priority to be high priority */
#define CCP2_HighPrioritySet()            (IPR2bits.CCP2IP =1)
/*This routine set the CCP2 Module priority to be low priority */
#define CCP2_LowPrioritySet()             (IPR2bits.CCP2IP =0)
#endif
#endif  

/********************************CCP2 END**********************************************/

/********************************EUSART TX START**********************************************/
#if EUSART_TX_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the EUSART TX Module*/
#define EUSART_TX_InterruptDisable()           (PIE1bits.TXIE=0)
/*This routine sets the interrupt enable for the EUSART TX Module*/
#define EUSART_TX_InterruptEnable()            (PIE1bits.TXIE=1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the EUSART TX Module priority to be high priority */
#define EUSART_TX_HighPrioritySet()            (IPR1bits.TXIP=1)
/*This routine set the EUSART TX Module priority to be low priority */
#define EUSART_TX_LowPrioritySet()             (IPR1bits.TXIP=0)
#endif
#endif  

/********************************EUSART TX END**********************************************/
/********************************EUSART RX START**********************************************/
#if EUSART_RX_INTERRUOT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the EUSART RX Module*/
#define EUSART_RX_InterruptDisable()           (PIE1bits.RCIE=0)
/*This routine sets the interrupt enable for the EUSART RX Module*/
#define EUSART_RX_InterruptEnable()            (PIE1bits.RCIE=1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the EUSART RX Module priority to be high priority */
#define EUSART_RX_HighPrioritySet()            (IPR1bits.RCIP=1)
/*This routine set the EUSART RX Module priority to be low priority */
#define EUSART_RX_LowPrioritySet()             (IPR1bits.RCIP=0)
#endif
#endif  

/********************************EUSART RX END**********************************************/

/********************************MSSP I2C START**********************************************/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine clears the interrupt enable for the MSSP I2C Module*/
#define MSSP_I2C_InterruptDisable()           (PIE1bits.SSPIE=0)
#define MSSP_I2C_BUS_COL_InterruptDisable()   (PIE2bits.BCLIE=0)
/*This routine sets the interrupt enable for the MSSP I2C Module*/
#define MSSP_I2C_InterruptEnable()            (PIE1bits.SSPIE=1)
#define MSSP_I2C_BUS_COL_InterruptEnable()    (PIE2bits.BCLIE=1)
/*This routine clears the interrupt flag for the MSSP I2C Module*/
#define MSSP_I2C_InterruptFlagClear()         (PIR1bits.SSPIF=0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear() (PIR2bits.BCLIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine set the MSSP I2C Module priority to be high priority */
#define MSSP_I2C_HighPrioritySet()            (IPR1bits.SSPIP=1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()    (IPR2bits.BCLIP=1)
/*This routine set the MSSP I2C Module priority to be low priority */
#define MSSP_I2C_LowPrioritySet()             (IPR1bits.SSPIP=0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()     (IPR2bits.BCLIP=0)
#endif
#endif  

/********************************MSSP I2C END**********************************************/
/* Section : Data Type Declarations */

/* Section : Function Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

