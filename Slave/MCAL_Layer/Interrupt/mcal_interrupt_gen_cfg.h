/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Nehal
 *
 * Created on September 15, 2023, 3:40 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* Section : Includes*/


/* Section : Macro Declarations */
#define INTERRUPT_FEATURE_ENABLE   1
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE  INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUOT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */
