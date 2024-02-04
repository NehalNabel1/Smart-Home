/* 
 * File:   hal_eeprom.h
 * Author:Nehal
 *
 * Created on September 27, 2023, 8:26 PM
 */

#include "hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData){
    Std_ReturnType ret=E_OK;
    /*Read the interrupt status (Enable or Disable)*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE ;
    /*Update the address register*/
    EEADRH= (uint8)((bAdd >>8) &0x03 );
    EEADR= (uint8)(bAdd & 0xFF);
    /*Update the data register*/
     EEDATA=bData;
     /*Select access data EEBROM memory*/
     EECON1bits.EEPGD=ACCESS_EEPROM_PROGRAM_MEMORY;
      EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY ;
     /*Allow write cycles to Flash memory/EEPROM*/
     EECON1bits.WREN=ALLOW_WRITE_CYCLE_FLASH_EEPROM;     
     /*Disable all interrupts "General interrupts*/
     INTERRUPT_GlobalInterruptDisable();
     /*Write the Required sequence 0x55 -> 0xAA*/
     EECON2=0x55;
     EECON2=0xAA;
     /*Initialize a data EEPROM erase/write cycle*/
     EECON1bits.WR=INITIATE_DATA_EEPROM_WRITE_ERASE;
     /*Wait for write to complete*/
     while(EECON1bits.WR)
     /*Inhibits write cycle to Flash program/data EEPROM*/
     EECON1bits.WREN=INHIBITS_WRITE_CYCLE_FLASH_EEPROM;
    /*Restore the interrupt status (Enable or Disable)*/
    INTCONbits.GIE=Global_Interrupt_Status;
    return ret;
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData){
    Std_ReturnType ret=E_NOT_OK;    
    if(NULL == bData){
        ret=E_NOT_OK;
    }
    else{
        /*Update the address register*/
        EEADRH= (uint8)((bAdd >>8) &0x03 );
        EEADR= (uint8)(bAdd & 0xFF);
        /*Select access data EEBROM memory*/
        EECON1bits.EEPGD=ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY ;
        /*Initialize a data EEPROM erase/write cycle*/
        EECON1bits.RD=INITIATE_DATA_EEPROM_READ ;
        NOP();
        NOP();
        /*Return the data*/
        *bData=EEDATA;
        ret=E_OK;
    }
    return ret;
    
}
