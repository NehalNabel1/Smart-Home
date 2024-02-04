/* 
 * File:   mcal_interrupt_config.h
 * Author: Nehal
 *
 * Created on September 15, 2023, 2:36 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* Section : Macro Declarations */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0


/* Section : Macro Function Declarations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This micro will enable priority levels*/
#define INTERRUPT_PriorityLevelEnable()         (RCONbits.IPEN=1)
/*This micro will disable priority levels*/
#define INTERRUPT_PriorityLevelDisable()        (RCONbits.IPEN=0)
/*This micro will enable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH=1)
/*This micro will disable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH=0)
/*This micro will enable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptLowEnable()    (INTCONbits.GIEL=1)
/*This micro will disable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptLowDisable()   (INTCONbits.GIEL=0)

#else

/*This micro will enable global interrupts*/
#define INTERRUPT_GlobalInterruptEnable()   (INTCONbits.GIE=1)
/*This micro will disable global interrupts*/
#define INTERRUPT_GlobalInterruptDisable()  (INTCONbits.GIE=0)
/*This micro will enable low priority global interrupts*/
/*This micro will enable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE=1)
/*This micro will disable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE=0)
#endif


/* Section : Data Type Declarations */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/* Section : Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

