/*
 *  Read_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_READ_SERVICES_H_
#define SERVICES_READ_SERVICES_H_

#include "Nand_Dri_Read.h"
#include "Protect_Services.h"
#include "StatusRegister_Services.h"

bool StandardRead_Service(uint32_t PageAddr, uint16_t ColAddr, uint8_t *Buffer, uint16_t Len);
bool RandomRead_Service(uint32_t PageAddr, uint16_t ColAddr, uint8_t *Buffer, uint16_t Len);

#endif /* SERVICES_READ_SERVICES_H_ */
