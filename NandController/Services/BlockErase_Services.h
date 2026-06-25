/*
 *  BlockErase_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_BLOCKERASE_SERVICES_H_
#define SERVICES_BLOCKERASE_SERVICES_H_

#include "Nand_Dri_Erase.h"
#include "Protect_Services.h"
#include "StatusRegister_Services.h"

#define BLOCK_ERASE_TIMEOUT 500

bool BlockErase128K_service(uint32_t BlockAddr, uint32_t Timeout);

#endif /* SERVICES_BLOCKERASE_SERVICES_H_ */
