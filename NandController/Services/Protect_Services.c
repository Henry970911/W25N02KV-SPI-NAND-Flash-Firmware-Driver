/*
 *  Protect_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include  "Protect_Services.h"

/**
 * @brief WriteEnable_Services
 * @detail
 * - Setting Status Register 3 (SR3) 中的 Write Enable Latch (WEL)
 * - Program / Erase / Status Register, 前置步驟
 *
 * @return true  : WEL = 1, Write Enable 成功
 * @return false : Retry 3 Times, Show Failed Message
 */
bool WriteEnable_Services(void)
{
	for (int i = 0; i < WRITE_RETRY; i++)
	{
		WriteEnable();

		if (IsWriteEnableLatch_service())
		{
			printf(" [WEL Enable 1] Success | Retry = %d\r\n", i);
			return true;
		}
	}

	printf(" [WEL Disable 0] Failed after %d retry\r\n", WRITE_RETRY);
	return false;
}

/** WriteDisable_Service
 *
 *  @brief  Send Write Disable (04h) Command, Clear Write Enable Latch (WEL)
 *
 *  @details
 *   - 清除 WEL 位元以防止後續的寫入或抹除操作
 *   - 通常於敏感操作完成後呼叫, 以避免誤寫
 *
 *  @note Write Disable 不需要 Write Enable 作為前置條件
 */
void WriteDisable_Services(void)
{
	WriteDisable();

	if (!IsWriteEnableLatch_service())
	{
		printf(" [WEL Disable 0] Disable Success\r\n");
	}
	else
	{
		printf(" [WEL Disable 1] Disable Failed\r\n");
	}
}

/// =========================== Status Register 1 ============================

/** SetBlockProtect_Service
 *
 *  @brief  設定 Status Register 1 的區塊保護範圍 (BP[3:0]) 與保護方向 (TB)
 *
 *  @details
 *   - BP[3:0]：定義受保護的區塊範圍大小
 *   - TB = 1：由高位址（Top）開始保護
 *   - TB = 0：由低位址（Bottom）開始保護
 *   - 設定完成後會讀回 SR1 進行驗證
 *   - 修改 SR1 前必須先執行 Write Enable
 *
 *  @param BPValue : 區塊保護值(0–15), 對應 BP[3:0]
 *  @param TB      : true -> Top 保護(TB = 1) | false -> Bottom 保護(TB = 0)
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SetBlockProtect_Service(uint8_t BPValue, bool TOPBottom)
{
	uint8_t SR1 = GetSR1();

	SR1 &= ~(SR1_BP3 | SR1_BP2 | SR1_BP1 | SR1_BP0 | SR1_TB);

	SR1 |= ((BPValue & 0x0F) << 3);

	if (TOPBottom)
	{
		SR1 |= SR1_TB;
	}

	WriteEnable_Services();
	WriteStatusRegister(ReadSR1, SR1);

	if (GetBlockProtectBits() == BPValue && IsTopBottomProtect() == TOPBottom)
	{
		printf("[Block Protect] Success (BP=0x%X, TB=%u)\r\n", GetBlockProtectBits(), IsTopBottomProtect());
		return true;
	}
	else
	{
		printf("[Block Protect] Failed (Expect BP=0x%X, TB=%u / Got BP=0x%X, TB=%u)\r\n", BPValue, TOPBottom, GetBlockProtectBits(), IsTopBottomProtect());
		return false;
	}
}

/** SetWriteProtectEnable_Service
 *
 *  @brief  設定 Status Register 1 中的 Write Protect Enable(WP-E)
 *
 *  @details
 *   - WP-E 用於啟用或停用寫入保護機制
 *   - 啟用後可能需要搭配硬體 WP# 腳位才能解除保護
 *
 *  @param enable true -> 啟用 WP-E | false -> 停用 WP-E
 *
 *  @return true  : 設定並驗證成功
 *  @return false : 寫入或驗證失敗
 */
bool SetWriteProtectEnable_Service(bool Enable)
{
	uint8_t SR1 = GetSR1();

	if (Enable)
		SR1 |= SR1_WPE;
	else
		SR1 &= ~SR1_WPE;

	WriteEnable_Services();
	WriteStatusRegister(ReadSR1, SR1);

	if (IsWriteProtectEnabled() == Enable)
	{
		printf("[SET WP-E] Success (WP-E = %u)\r\n", IsWriteProtectEnabled());
		return true;
	}
	else
	{
		printf("[SET WP-E] Failed (Expect WP-E = %u / Got WP-E = %u)\r\n", Enable, IsWriteProtectEnabled());
		return false;
	}
}

/** SetStatusRegisterProtect_Service
 *
 *  @brief  設定 Status Register Protect 位元 (SRP0 / SRP1)
 *
 *  @details
 *   - SRP 位元用於控制狀態暫存器是否可再次被修改
 *   - 啟用後可能需要硬體 WP# 或重新上電才能解除
 *
 *  @param srp0 SRP0 設定值
 *  @param srp1 SRP1 設定值
 *
 *  @return true  : 設定並驗證成功
 *  @return false : 寫入或驗證失敗
 */
bool SetStatusRegisterProtect_Service(bool SRP0, bool SRP1)
{
	uint8_t SR1 = GetSR1();

	/// Clear old SRP bits
	SR1 &= ~(SR1_SRP0 | SR1_SRP1);

	if (SRP0)
		SR1 |= SR1_SRP0;
	if (SRP1)
		SR1 |= SR1_SRP1;

	WriteEnable_Services();
	WriteStatusRegister(ReadSR1, SR1);

	if (IsSRP0Enabled() == SRP0 && IsSRP1Enabled() == SRP1)
	{
		printf("[SET SRP] Success (SRP0 = %u, SRP1 = %u)\r\n", IsSRP0Enabled(), IsSRP1Enabled());
		return true;
	}
	else
	{
		printf("[SET SRP] Failed (Expect SRP0 = %u, SRP1 = %u / Got SRP0 = %u, SRP1 = %u)\r\n", SRP0, SRP1, IsSRP0Enabled(), IsSRP1Enabled());
		return false;
	}
}

/// ==========================================================================

/// =========================== Status Register 2 ============================

/** OTPLock_Service
 *
 *  @brief  永久鎖定 OTP 區域（設定 SR2 中的 OTPL 位元）
 *
 *  @details
 *   - 將 Status Register 2（SR2）中的 OTPL 位元設為 1
 *   - 設定後，OTP（One-Time Programmable）區域將變為唯讀
 *   - 此操作為「不可逆行為」，一旦鎖定即無法解除
 *   - 通常用於正式量產或安全性需求場景
 *
 *  @return true  : OTP 區域鎖定成功 (OTPL = 1)
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool OTPLock_Service(void)
{
	uint8_t SR2 = GetSR2();
	SR2 |= SR2_OTPL;

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (GetOTP_Lock_service())
	{
		printf("[SET OTP-L] Success (OTP-L = 1, Locked permanently)\r\n");
		return true;
	}
	else
	{
		printf("[SET OTP-L] Failed (OTP-L not set)\r\n");
		return false;
	}
}

/** OTPEnable_Service
 *
 *  @brief  啟用或停用 OTP 模式 (設定 SR2 中的 OTP-E 位元)
 *
 *  @details
 *   - OTP-E 用於控制是否進入 OTP 操作模式
 *   - 啟用後，相關存取行為將指向 OTP 區域
 *
 *  @param enable : true -> 啟用 OTP 模式 (OTP-E = 1) | false -> 停用 OTP 模式 (OTP-E = 0)
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool OTPEnable_Service(bool Enable)
{
	uint8_t SR2 = GetSR2();

	if (Enable)
		SR2 |= SR2_OTPE;
	else
		SR2 &= ~SR2_OTPE;

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (IsOTPEnabled_service() == Enable)
	{
		printf("[SET OTP-E] Success (OTP-E = %u)\r\n", IsOTPEnabled_service());
		return true;
	}
	else
	{
		printf("[SET OTP-E] Failed (Expect OTP-E = %u / Got OTP-E = %u)\r\n", Enable, IsOTPEnabled_service());
		return false;
	}
}

/** SR1Lock_Service
 *
 *  @brief  永久鎖定 Status Register 1 (設定 SR2 中的 SR1-L 位元)
 *
 *  @details
 *   - 將 SR1-L 位元設為 1, 使 SR1 無法再被修改
 *   - 此操作為不可逆, 通常用於防止保護設定被竄改
 *
 *  @return true  : SR1 鎖定成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SR1Lock_Service(void)
{
	uint8_t SR2 = GetSR2();
	SR2 |= SR2_SR1L; // SR1-L = 1 (永久鎖定)

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (IsSR1Locked_service())
	{
		printf("[SET SR1-L] Success (SR1-L = 1, Locked permanently)\r\n");
		return true;
	}
	else
	{
		printf("[SET SR1-L] Failed (SR1-L not set)\r\n");
		return false;
	}
}

/** SetECCEnable_Service
 *
 *  @brief  啟用或停用 NAND 內建 ECC 引擎(設定 SR2 中的 ECC-E 位元)
 *
 *  @details
 *   - ECC-E 用於控制 NAND 內部 ECC 校正機制。
 *   - 建議在所有 Read 操作前啟用 ECC。
 *
 *  @param enable true -> 啟用 ECC | false -> 停用 ECC
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SetECCEnable_Service(bool Enable)
{
	uint8_t SR2 = GetSR2();

	if (Enable)
		SR2 |= SR2_ECCE;
	else
		SR2 &= ~SR2_ECCE;

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (IsECCEnabled_service() == Enable)
	{
		printf("[SET ECC] Success (ECC-E = %u)\r\n", IsECCEnabled_service());
		return true;
	}
	else
	{
		printf("[SET ECC] Failed (Expect ECC-E = %u / Got ECC-E = %u)\r\n", Enable, IsECCEnabled_service());
		return false;
	}
}

/** SetBufferMode_Service
 *
 *  @brief  啟用或停用 Buffer Read 模式（設定 SR2 中的 BUF 位元）
 *
 *  @details
 *   - BUF 位元用於控制是否啟用 Buffer 模式進行讀取。
 *   - 影響 Read Data 行為與效能。
 *
 *  @param enable true -> 啟用 Buffer 模式 | false -> 停用 Buffer 模式
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SetBufferMode_Service(bool Enable)
{
	uint8_t SR2 = GetSR2();

	if (Enable)
		SR2 |= SR2_BUF;
	else
		SR2 &= ~SR2_BUF;

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (IsBufferMode_service() == Enable)
	{
		printf("[SET BUF] Success (BUF = %u)\r\n", IsBufferMode_service());
		return true;
	}
	else
	{
		printf("[SET BUF] Failed (Expect BUF = %u / Got BUF = %u)\r\n", Enable, IsBufferMode_service());
		return false;
	}
}

/** SetOutputDriverStrength_Service
 *
 *  @brief  設定輸出驅動強度（ODS[2:0]，位於 SR2）
 *
 *  @details
 *   - ODS 用於調整輸出驅動能力。
 *   - 實際可用等級依 datasheet 定義。
 *
 *  @param level 輸出驅動強度等級(0 ~ 3)
 *
 *  @return true  : 設定並驗證成功
 *  @return false : 參數不合法或設定驗證失敗
 */
bool SetOutputDriverStrength_Service(uint8_t Level)
{
	if (Level > 3)
		return false;

	uint8_t SR2 = GetSR2();

	SR2 &= ~SR2_ODS_MASK;
	SR2 |= (Level << 1);

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	if (GetOutputDriverStrength_service() == Level)
	{
		printf("[SET ODS] Success (ODS = %u)\r\n", GetOutputDriverStrength_service());
		return true;
	}
	else
	{
		printf("[SET ODS] Failed (Expect ODS = %u / Got ODS = %u)\r\n", Level, GetOutputDriverStrength_service());
		return false;
	}
}

/** SetHoldDisable_Service
 *
 *  @brief  啟用或停用 HOLD# 腳位功能(設定 SR2 中的 H-DIS 位元)
 *
 *  @details
 *   - 當 H-DIS = 1 時，HOLD# 腳位功能被停用。
 *   - 可避免 HOLD# 腳位誤觸造成通訊中斷。
 *
 *  @param disable true -> 停用 HOLD# 腳位 | false -> 啟用 HOLD# 腳位
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SetHoldDisable_Service(bool Disable)
{
	uint8_t SR2 = GetSR2();

	if (Disable)
		SR2 |= SR2_HDIS;
	else
		SR2 &= ~SR2_HDIS;

	if (!WriteEnable_Services())
	{
		return false;
	}

	WriteStatusRegister(ReadSR2, SR2);

	if (IsHoldDisabled_service() == Disable)
	{
		printf("[SET H-DIS] Success (H-DIS = %u)\r\n", IsHoldDisabled_service());
		return true;
	}
	else
	{
		printf("[SET H-DIS] Failed (Expect H-DIS = %u / Got H-DIS = %u)\r\n", Disable, IsHoldDisabled_service());
		return false;
	}
}

/** SetReadMode_Service
 *
 *  @brief  一次性設定讀取模式 (同時設定 BUF 與 ECC-E)
 *
 *  @details
 *   - 同時控制 Buffer Mode 與 ECC 功能
 *   - 常用於初始化或讀取模式切換
 *
 *  @param buf true -> 啟用 Buffer 模式
 *  @param ecc true -> 啟用 ECC 功能
 *
 *  @return true  : 設定並驗證成功
 *  @return false : Write Enable 失敗或設定驗證失敗
 */
bool SetReadMode_Service(bool BUF, bool ECC)
{
	uint8_t SR2 = GetSR2();

	/// 清除原有 BUF 與 ECC-E
	SR2 &= ~(SR2_BUF | SR2_ECCE);

	/// 設定新的值
	if (BUF)
		SR2 |= SR2_BUF;
	if (ECC)
		SR2 |= SR2_ECCE;

	if (!WriteEnable_Services())
		return false;

	WriteStatusRegister(ReadSR2, SR2);

	bool NewBuf = IsBufferMode_service();
	bool NewEcc = IsECCEnabled_service();

	if (NewBuf == BUF && NewEcc == ECC)
	{
		printf("[SET ReadMode] Success (BUF=%u, ECC-E=%u)\r\n", NewBuf, NewEcc);
		return true;
	}
	else
	{
		printf("[SET ReadMode] Failed (Expect BUF=%u,ECC-E=%u / Got BUF=%u,ECC-E=%u)\r\n", BUF, ECC, NewBuf, NewEcc);
		return false;
	}
}

/// ==========================================================================

/// =========================== Status Register 3 ============================

/** IsBusyWithTimeout_service
 *
 *  @brief 輪詢 Status Register 3(SR3) 中的 OIP (Operation In Progress),
 *         直到裝置就緒或逾時發生
 *
 *  @details
 *   - OIP 位元用於表示 NAND 裝置是否仍在執行內部操作（Program / Erase）。
 *   - 當 OIP = 1 時，表示裝置 Busy，尚未完成內部動作。
 *   - 當 OIP = 0 時，表示裝置已就緒，可接受下一筆指令。
 *   - 若在指定的 timeout 時間內 OIP 仍未清除，則視為逾時失敗。
 *   - 常用於 Program、Erase 或 Reset 指令後的狀態同步。
 *
 *  @param timeout_ms : 等待裝置就緒的最長時間（單位：毫秒）
 *
 *  @return true   : 裝置已就緒（OIP = 0）
 *  @return false  : 在指定時間內裝置仍為 Busy 狀態（逾時）
 */
bool IsBusyWithTimeout_service(uint32_t Timeout)
{
	uint32_t START = HAL_GetTick();

	while ((HAL_GetTick() - START) < Timeout)
	{
		if (!IsBusy_service())
		{
			printf("[OIP Status : 0] Device is Ready\r\n");
			return true;
		}
	}

	printf("[OIP Status : 1] Timeout Failed\r\n");
	return false;
}

/// ==========================================================================
