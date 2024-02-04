/* 
 * File:   hal_eeprom.h
 * Author:Nehal
 *
 * Created on September 27, 2023, 8:26 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : Includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declarations */
#define ACCESS_FLASH_PROGRAM_MEMORY 1
#define ACCESS_EEPROM_PROGRAM_MEMORY 0
#define ACCESS_CONFIG_REGISTERS 1
#define ACCESS_FLASH_EEPROM_MEMORY  0
#define ALLOW_WRITE_CYCLE_FLASH_EEPROM 1
#define INHIBITS_WRITE_CYCLE_FLASH_EEPROM 1
#define INITIATE_DATA_EEPROM_WRITE_ERASE 1
#define DATA_EEPROM_WRITE_ERASE_COMPELETED 0
#define INITIATE_DATA_EEPROM_READ 1
/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData);

#endif	/* HAL_EEPROM_H */

