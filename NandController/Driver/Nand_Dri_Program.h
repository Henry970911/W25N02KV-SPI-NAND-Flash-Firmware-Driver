/*
 *  Nand_Dri_Program.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef DRIVER_NAND_DRI_PROGRAM_H_
#define DRIVER_NAND_DRI_PROGRAM_H_

#include "Nand_Hal.h"

#define CMD_LOAD_PROGRAM_DATA             0x02
#define CMD_RANDOM_LOAD_PROGRAM_DATA      0x84
#define CMD_QUAD_LOAD_PROGRAM_DATA        0x32
#define CMD_QUAD_RANDOM_LOAD_PROGRAM_DATA 0x34
#define CMD_PROGRAM_EXECUTE               0x10

void LoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len);
void RandomLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len);
void QuadLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len);
void QuadRandomLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len);
void ProgramExecute(uint32_t PageAddr);

#endif /* DRIVER_NAND_DRI_PROGRAM_H_ */
