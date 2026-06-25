/*
 *  BlockErase_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include "BlockErase_Services.h"

/** BlockErase128K_service
 *
 *  @brief  執行 W25N02KV NAND Flash 的 128KB 區塊抹除操作
 *
 *  @details
 *   - Erase 1 Block (128KB = 64 Pages * 2KB)
 *   - After Erase Block, All Page Data 0xFF of Block
 *
 *  @param block_addr : 目標 Block 位址(Block Index * 128KB)
 *  @param timeout_ms : 抹除操作允許的最長等待時間(毫秒)
 *
 *  @return true   : Erase Success(無逾時、E_FAIL=0, 且流程正常)
 *  @return false  : Erase Failed、RunTime Failed or Status Failed
 */
bool BlockErase128K_service(uint32_t BlockAddr, uint32_t Timeout)
{
	/// Step 1: 解除所有 Block 保護（BP = 0，允許抹除）
	if (!SetBlockProtect_Service(0x0, false))
	{
		printf("[Initialization] Failed to unlock all Blocks\r\n");
	}

	/// Step 2: 設定 Write Enable Latch（WEL = 1）
	if (!WriteEnable_Services())
	{
		printf("[Block Erase] Write Enable Failed\r\n");
		return false;
	}

	/// Step 3: 發送 Block Erase 指令（D8h）
	BlockErase(BlockAddr);

	/// Step 4: 輪詢 OIP，等待抹除完成
	if (!IsBusyWithTimeout_service(Timeout))
	{
		printf("[Block Erase] Timeout\r\n");
		return false;
	}

	printf("[SR After ] SR1=0x%02X SR2=0x%02X SR3=0x%02X\r\n", GetSR1(), GetSR2(), GetSR3());

	/// Step 5: 檢查 E_FAIL
	if (CheckEraseFail_service())
	{
		printf("[Block Erase] Failed (E-FAIL = 1)\r\n");
		return false;
	}

	/// Step 6: 確認 WEL 是否已在抹除後自動清除
	if (IsWriteEnableLatch_service())
	{
		printf("[Block Erase] Warning: WEL not cleared after erase\r\n");
	}

	printf("[Block Erase] Success (Block = 0x%06lX)\r\n", BlockAddr);
	return true;
}
