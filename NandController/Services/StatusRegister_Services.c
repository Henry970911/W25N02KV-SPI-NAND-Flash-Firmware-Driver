/*
 *  StatusRegister_Services.c
 *
 *  Created on: Mar 1, 2026
 *  Author: Henry
 */

#include "StatusRegister_Services.h"

/// =========================== Status Register 1 ============================

uint8_t GetSR1(void)
{
	return ReadStatusRegister(ReadSR1);
}

uint8_t GetBlockProtectBits(void)
{
	return (GetSR1() & (SR1_BP3 | SR1_BP2 | SR1_BP1 | SR1_BP0)) >> 3;
}

bool IsTopBottomProtect(void)
{
	return (GetSR1() & SR1_TB) ? true : false;
}

bool IsWriteProtectEnabled(void)
{
	return (GetSR1() & SR1_WPE) ? true : false;
}

bool IsSRP0Enabled(void)
{
	return (GetSR1() & SR1_SRP0) ? true : false;
}

bool IsSRP1Enabled(void)
{
	return (GetSR1() & SR1_SRP1) ? true : false;
}

/// ==========================================================================

/// =========================== Status Register 2 ============================

uint8_t GetSR2(void)
{
	return ReadStatusRegister(ReadSR2);
}

bool GetOTP_Lock_service(void)
{
	return (GetSR2() & SR2_OTPL) ? true : false;
}

bool IsOTPEnabled_service(void)
{
	return (GetSR2() & SR2_OTPE) ? true : false;
}

bool IsSR1Locked_service(void)
{
	return (GetSR2() & SR2_SR1L) ? true : false;
}

bool IsECCEnabled_service(void)
{
	return (GetSR2() & SR2_ECCE) ? true : false;
}

bool IsBufferMode_service(void)
{
	return (GetSR2() & SR2_BUF) ? true : false;
}

uint8_t GetOutputDriverStrength_service(void)
{
	return (GetSR2() & SR2_ODS_MASK) >> 1;
}

bool IsHoldDisabled_service(void)
{
	return (GetSR2() & SR2_HDIS) ? true : false;
}

/// ==========================================================================

/// =========================== Status Register 3 ============================

uint8_t GetSR3(void)
{
	return ReadStatusRegister(ReadSR3);
}

bool IsWriteEnableLatch_service(void)
{
	return (GetSR3() & SR3_WEL) ? true : false;
}

bool IsBusy_service(void)
{
	return (GetSR3() & SR3_BUSY) ? true : false;
}

bool CheckProgramFail_service(void)
{
	return (GetSR3() & SR3_PFAIL) ? true : false;
}

bool CheckEraseFail_service(void)
{
	return (GetSR3() & SR3_EFAIL) ? true : false;
}

bool IsECCError_service(void)
{
	ECC_Status_t ecc_status = GetECCStatus_service();

	return (ecc_status == ECC_UNCORRECTABLE || ecc_status == ECC_CORRECTED_THRESHOLD);
}

ECC_Status_t GetECCStatus_service(void)
{
	uint8_t sr3 = GetSR3();
	uint8_t ecc_bits = (sr3 & SR3_ECC_MASK) >> 4;

	switch (ecc_bits)
	{
	case 0b000:
		return ECC_SUCCESS;
	case 0b001:
		return ECC_SUCCESS_CORRECTED;
	case 0b010:
		return ECC_UNCORRECTABLE;
	case 0b011:
		return ECC_CORRECTED_THRESHOLD;
	default:
		printf("[Warning] ECC Reserved code : 0b%03u (SR3 = 0x%02X)\r\n", ecc_bits, sr3);
		return ECC_SUCCESS;
	}
}

/// ==========================================================================
