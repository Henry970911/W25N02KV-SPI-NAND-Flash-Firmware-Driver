/*
 *  OTP_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_OTP_SERVICES_H_
#define SERVICES_OTP_SERVICES_H_

#include "Nand_Dri_Read.h"
#include "Nand_Dri_Program.h"
#include "Protect_Services.h"
#include "StatusRegister_Services.h"

#define OTP_PAGE_UNIQUE_ID   0x00
#define OTP_PAGE_PARAMETER   0x01
#define OTP_PAGE0            0x02
#define OTP_PAGE_MAX         0x0B

bool OTP_ReadPage(uint8_t OTP_PageIndex, uint8_t *Buffer, uint16_t Len);
bool OTP_ProgramPage(uint8_t OTP_PageIndex, const uint8_t *Buffer, uint16_t Len);

#endif /* SERVICES_OTP_SERVICES_H_ */
