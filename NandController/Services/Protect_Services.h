/*
 *  Protect_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_PROTECT_SERVICES_H_
#define SERVICES_PROTECT_SERVICES_H_

#include "Nand_Dri_Protect.h"
#include "StatusRegister_Services.h"

#define WRITE_RETRY 3

bool WriteEnable_Services(void);
void WriteDisable_Services(void);

/// =========================== Status Register 1 ============================

bool SetBlockProtect_Service(uint8_t BpValue, bool TopBottom);
bool SetWriteProtectEnable_Service(bool Enable);
bool SetStatusRegisterProtect_Service(bool SRP0, bool SRP1);

/// ==========================================================================

/// =========================== Status Register 2 ============================

bool OTPLock_Service(void);								/// OTP-L (一次性鎖)
bool OTPEnable_Service(bool Enable);					/// OTP-E
bool SR1Lock_Service(void);								/// SR1-L (一次性鎖)
bool SetECCEnable_Service(bool Enable);					/// ECC-E
bool SetBufferMode_Service(bool Enable);				/// BUF
bool SetOutputDriverStrength_Service(uint8_t Level);	/// ODS[1:0]
bool SetHoldDisable_Service(bool Disable);				/// H-DIS
bool SetReadMode_Service(bool BUF, bool ECC);

/// ==========================================================================

/// =========================== Status Register 3 ============================

bool IsBusyWithTimeout_service(uint32_t Timeout); 		/// 單位:ms

/// ==========================================================================

#endif /* SERVICES_PROTECT_SERVICES_H_ */
