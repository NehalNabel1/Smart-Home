/* 
 * File:   TemSensor_TC74.h
 * Author: Nehal
 *
 * Created on December 10, 2023, 10:50 AM
 */

#ifndef TEMSENSOR_TC74_H
#define	TEMSENSOR_TC74_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../../MCAL_Layer/I2C/hal_i2c.h"

extern mssp_i2c_t i2c_obj;

uint8 TemSensor_TC74_Read_Temp(uint8 TC74_Address);


#endif	/* TEMSENSOR_TC74_H */

