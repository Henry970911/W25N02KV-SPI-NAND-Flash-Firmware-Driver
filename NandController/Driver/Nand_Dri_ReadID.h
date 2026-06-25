/*
 *  Nand_ReadID.h
 *
 *  Created on: Feb 25, 2026
 *  Author: CPC
 */

#ifndef DRIVER_NAND_DRI_READID_H_
#define DRIVER_NAND_DRI_READID_H_

#include <Nand_Hal.h>

#define JEDECID 0x9F

void W25N02KV_ReadJEDECID(uint8_t *buf);

#endif /* DRIVER_NAND_DRI_READID_H_ */
