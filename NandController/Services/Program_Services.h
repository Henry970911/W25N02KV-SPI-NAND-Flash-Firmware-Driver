/*
 *  Program_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_PROGRAM_SERVICES_H_
#define SERVICES_PROGRAM_SERVICES_H_

#include "Nand_Dri_Program.h"
#include "Protect_Services.h"
#include "StatusRegister_Services.h"

bool StandardProgram_Service(uint32_t PageAddr, const uint8_t *Buffer, uint16_t Len);
bool RandomProgram_Service(uint32_t PageAddr, uint16_t ColAddr, const uint8_t *Buffer, uint16_t Len);

#endif /* SERVICES_PROGRAM_SERVICES_H_ */
