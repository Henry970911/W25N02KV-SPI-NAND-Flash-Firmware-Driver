/*
 *  Nand_Dri_StatusRegister.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef DRIVER_NAND_DRI_STATUSREGISTER_H_
#define DRIVER_NAND_DRI_STATUSREGISTER_H_

#include "Nand_Hal.h"

#define CMD_READ_SR  0x05
#define CMD_WRITE_SR 0x01

uint8_t ReadStatusRegister(uint8_t SrAddr);
void WriteStatusRegister(uint8_t SrAddr, uint8_t Value);

#endif /* DRIVER_NAND_DRI_STATUSREGISTER_H_ */
