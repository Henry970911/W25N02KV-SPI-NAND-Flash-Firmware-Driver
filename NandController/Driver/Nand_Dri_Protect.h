/*
 *  Nand_Dri_Protect.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef DRIVER_NAND_DRI_PROTECT_H_
#define DRIVER_NAND_DRI_PROTECT_H_

#include "Nand_Hal.h"

#define CMD_WRITE_ENABLE  0x06
#define CMD_WRITE_DISABLE 0x04

void WriteEnable(void);
void WriteDisable(void);

#endif /* DRIVER_NAND_DRI_PROTECT_H_ */
