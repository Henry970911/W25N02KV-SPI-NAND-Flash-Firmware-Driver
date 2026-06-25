/*
 *  Test_FactoryInvalidBlockScan.c
 *
 *  Created on: Mar 2, 2026
 *  Author: CPC
 */

#include "Test_FactoryInvalidBlockScan.h"

/** ScanInvaliBlocks
 *
 *  @brief Bad Block 掃描驗證測試(避開系統保留區塊)
 *
 *  @details
 *   - 本函式用於掃描 NAND 中所有出廠即標記為壞的 Block
 *   - 壞區塊判斷依據：
 *     => 讀取該 Block 的 Page0
 *     => 檢查 Spare Area 的第 1 個位元組 (spare[0])
 *     => 若 spare[0] != 0xFF，視為 Factory Bad Block
 *   - 掃描時排除系統保留區塊 : Block (0 ~ 7) ~ (2044 ~ 2047)
 *
 *  @param None
 *
 *  @return 掃描結果將透過 USART 輸出
 */
void ScanInvaliBlocks(void)
{
	printf("=========================================================\r\n");
	printf("============ [Scan Invalid Block Test Start] ============\r\n");

	/// Step 1: 裝置重置與狀態暫存器清除
	SoftwareReset_Service();

	/// Step 2:
	/// Factory Bad Block 掃描
	/// - 掃描範圍：Block 8 ~ Block 2043
	/// - 判斷條件：spare[0] != 0xFF
	/// - Block 0~7 與 2044~2047 為保留區塊，視為有效
	BBT_ScanFactoryBlocks();

	/// Step 3: 輸出 Block 數量與壞區塊數量
	BBT_PrintSummary();

	/// Step 4: 輸出 Factory Bad Block 清單
	BBT_ShowBadBlock();

	printf("=========== [Scan Invalid Block Test Finished] ==========\r\n");
	printf("=========================================================\r\n");
}

/** ChoseValidBlock
 *
 *  @brief (延伸測試)掃描 Bad Block 後, 選擇第一個可用的有效 Block 並執行基本測試
 *
 *  @details
 *   - 本函式會先執行完整的 Factory Bad Block 掃描
 *   - 從 Bad Block Table（BBT）中尋找第一個有效 Block
 *   - 若成功找到有效 Block，則執行基本單元測試流程：
 *     => Erase
 *     => Program
 *     => Read / Verify
 *   - 若無任何可用 Block，則輸出錯誤訊息
 *
 *  @param None
 *
 *  @return None
 *   - 測試與選擇結果皆透過 Console Log 顯示
 */
void ChoseValidBlock(void)
{
	/// Step 1:
	/// 執行 Factory Bad Block 掃描
	/// - 確保 BBT 資料為最新狀態
	ScanInvaliBlocks();

	/// Step 2:
	/// 從 BBT 中取得第一個有效 Block Index
	/// - 若回傳值 < 0，表示無可用 Block
	int validBlock = FindFirstValidBlock();
	printf("\r\n");

	/// Step 3:
	/// 對第一個有效 Block 執行基本功能測試
	/// - 使用 Standard_UnitTest() 驗證基本 P/E/R 流程
	if (validBlock >= 0)
	{
		printf("First Valid Block : %d\r\n", validBlock);
		Standard_UnitTest(validBlock);
	}
	else
	{
		printf("No valid block available !\r\n");
	}
}
