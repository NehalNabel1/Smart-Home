/* 
 * File:   EEPROM_24C02C.h
 * Author: Nehal
 *
 * Created on December 9, 2023, 8:27 PM
 */

#ifndef EEPROM_24C02C_H
#define	EEPROM_24C02C_H

/* Section : Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../../MCAL_Layer/I2C/hal_i2c.h"

extern mssp_i2c_t i2c_obj;


/* Section : Function Declarations */
void EEPROM_24C02C_Write_Byte(uint8 EEPROM_Address,uint8 Byte_Address ,uint8 Data);
uint8 EEPROM_24C02C_Read_Byte(uint8 EEPROM_Address,uint8 Byte_Address );

#endif	/* EEPROM_24C02C_H */

