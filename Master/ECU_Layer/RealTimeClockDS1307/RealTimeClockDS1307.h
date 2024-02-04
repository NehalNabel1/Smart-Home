/* 
 * File:   RealTimeClockDS1307.h
 * Author: Nehal
 *
 * Created on November 30, 2023, 8:52 PM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../../MCAL_Layer/I2C/hal_i2c.h"
#include"../../MCAL_Layer/USART/hal_usart.h"
#include"../Chr_LCD/ecu_chr_lcd.h"

extern mssp_i2c_t i2c_obj;
extern usart_t usart_obj;
extern chr_lcd_8bit_t lcd_2;


typedef struct {
    uint8 _Hours ;
    uint8 _Minutes ;
    uint8 _Seconds ;
    uint8 _Year ;
    uint8 _Month ;
    uint8 _Day;
    
}RealTimeClockDS1307_T;

RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void);
void Print_RealTimeClockDS1307(void);
#endif	/* REALTIMECLOCKDS1307_H */
