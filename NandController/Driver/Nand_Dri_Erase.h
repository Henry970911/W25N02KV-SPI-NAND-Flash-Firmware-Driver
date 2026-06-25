/*
 *  Nand_Dri_Erase.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef DRIVER_NAND_DRI_ERASE_H_
#define DRIVER_NAND_DRI_ERASE_H_

#include "Nand_Hal.h"

#define CMD_EraseBy128K 0xD8

void BlockErase(uint32_t BlockAddr);

#endif /* DRIVER_NAND_DRI_ERASE_H_ */
