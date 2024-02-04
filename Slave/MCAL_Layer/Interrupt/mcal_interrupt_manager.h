/* 
 * File:   mcal_interrupt_manager.h
 * Author: Dubai
 *
 * Created on September 15, 2023, 2:47 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes*/
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
void INT0_ISR();
void INT1_ISR();
void INT2_ISR();

void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);

void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_Tx_ISR(void);
void EUSART_Rx_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
   
#endif	/* MCAL_INTERRUPT_MANAGER_H */

