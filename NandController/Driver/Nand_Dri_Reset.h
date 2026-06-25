/*
 *  Nand_Dri_Reset.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef DRIVER_NAND_DRI_RESET_H_
#define DRIVER_NAND_DRI_RESET_H_

#include "Nand_Hal.h"

/* ---------------------------------------------------------------------------
 * Command Code Definition
 * ---------------------------------------------------------------------------
 * CMD_RESET        : 99h
 * CMD_ENABLE_RESET : 66h
 * CMD_DEVICE_RESET : FFh
 * --------------------------------------------------------------------------- */
#define CMD_RESET 0x99
#define CMD_ENABLE_RESET 0x66
#define CMD_DEVICE_RESET 0xFF

/* ---------------------------------------------------------------------------
 * Command driver
 * ---------------------------------------------------------------------------
 * Reset       : Send 66h command to enable reset
 * EnableReset : Send 99h command to perform software reset
 * DeviceReset : Send FFh command to perform full device reset
 * --------------------------------------------------------------------------- */
void Reset(void);
void EnableReset(void);
void DeviceReset(void);

#endif /* DRIVER_NAND_DRI_RESET_H_ */
