/*
 *  BBT_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include "BBT_Services.h"

bool BBT_Table[TOTAL_BLOCKS]; /// Invalid Block Table

extern bool StandardRead_Service(uint32_t PageAddr, uint16_t ColAddr, uint8_t *Buf, uint16_t Len);
extern void LoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len);
extern void ProgramExecute(uint32_t PageAddr);
extern bool IsBusyWithTimeout_service(uint32_t Timeout);
extern bool CheckProgramFail_service(void);

/** @brief 讀取指定 Block 的 Page0 中壞區塊標記位元
 *
 *  @details
 *   - 讀取目標 Block 的第 0 頁 (Page0) 中:
 *     => Main Area  的第 1 個位元組 (main[0])
 *     => Spare Area 的第 1 個位元組 (spare[0])
 *   - 此兩個位元組用於判斷是否為出廠壞區塊（Factory Bad Block）
 *   - 正常良好區塊應同時滿足 : main[0] == 0xFF 且 spare[0] == 0xFF
 *
 *  @param block : 目標 Block 索引
 *  @param m0    : 用於接收 main[0] 資料的緩衝區指標
 *  @param s0    : 用於接收 spare[0] 資料的緩衝區指標
 *
 *  @return true   : 成功讀取兩個標記位元組
 *  @return false  : 讀取流程失敗
 */
static bool read_marker_bytes_page0(uint32_t Block, uint8_t *MAIN0, uint8_t *SPARE0)
{
	uint32_t Page0 = PAGE_ADDR(Block, 0);

	/// Step 1: 讀取 Page0 的 main[0]
	if (!StandardRead_Service(Page0, 0, MAIN0, 1))
		return false;

	/// Step 2: 讀取 Page0 的 spare[0]
	if (!StandardRead_Service(Page0, PAGE_MAIN_SIZE, SPARE0, 1))
		return false;

	return true;
}

/** @brief 判斷指定 Block 是否為出廠標記的壞區塊
 *
 *  @details
 *   - 透過讀取 Page0 的 main[0] 與 spare[0] 標記位元組進行判斷。
 *   - 判定規則如下：
 *     - 若 main[0] != 0xFF 或 spare[0] != 0xFF，則視為壞區塊。
 *   - 呼叫前會先將輸出值初始化為 0xFF，以確保資料乾淨。
 *
 *  判斷邏輯：
 *   if (main0 != 0xFF) || (spare0 != 0xFF) → Factory Bad Block
 *
 *  @param block  : 目標 Block 索引
 *  @param main0  : 用於儲存 main[0] 值的變數指標
 *  @param spare0 : 用於儲存 spare[0] 值的變數指標
 *
 *  @return true   : 判定為出廠壞區塊
 *  @return false  : 判定為良好區塊或讀取失敗
 */
static bool is_factory_bad(uint32_t Block, uint8_t *MAIN0, uint8_t *SPARE0)
{
	/// Step 1: 初始化標記位元組
	*MAIN0 = 0xFF;
	*SPARE0 = 0xFF;

	/// Step 2: 讀取 Page0 的標記位元組
	if (!read_marker_bytes_page0(Block, MAIN0, SPARE0))
		return false;

	/// Step 3: 判斷是否為出廠壞區塊
	return (*MAIN0 != 0xFFu) || (*SPARE0 != 0xFFu);
}

/** @brief 將 Runtime 壞區塊標記寫入 Page0 的 spare[0]
 *
 *  @details
 *   - 當系統於運行期間偵測到 Block 發生程式或抹除錯誤時，
 *     透過此函式將該 Block 標記為壞區塊。
 *   - 寫入方式為：
 *     在 Page0 的 spare[0] 寫入 0x00，並執行 Program Execute。
 *   - 此標記一經寫入即為永久性，不可回復。
 *
 *  Flow：
 *   1. 將 0x00 載入至 spare[0]（Page Buffer）
 *   2. 執行 Program Execute，寫入 NAND
 *   3. 等待程式完成（Polling OIP）
 *   4. 檢查 Program Fail 狀態
 *
 *  @param block : 欲標記為壞區塊的 Block 索引
 */
static void write_bad_marker_page0_spare0(uint32_t Block)
{
	uint32_t Page0 = PAGE_ADDR(Block, 0);
	uint8_t Mark = 0x00;

	/// Step 1: 將壞區塊標記值 0x00 載入至 spare[0]
	LoadProgramData(PAGE_MAIN_SIZE, &Mark, 1);

	/// Step 2: 執行 Program Execute，寫入 Page0
	ProgramExecute(Page0);

	/// Step 3: 等待寫入完成
	if (!IsBusyWithTimeout_service(100))
	{
		printf("[Invalid Table] Timeout while marking bad block\r\n");
		return;
	}

	/// Step 4: 檢查 Program Fail 狀態
	if (CheckProgramFail_service())
	{
		printf("[Invalid Table] Failed to program bad block marker\r\n");
	}
	else
	{
		printf("[Invalid Table] Permanent marker written (Block:%lu)\r\n", (unsigned long) Block);
	}
}

/** @brief 掃描所有 Block，並依據出廠壞區塊標記建立 Bad Block Table (BBT)
 *
 *  @details
 *   - 逐一讀取每個 Block 的第 0 頁（Page0），檢查出廠壞區塊標記。
 *   - 透過讀取：
 *     - Main Area 的 main[0]
 *     - Spare Area 的 spare[0]
 *   - 若任一位元組不為 0xFF，則判定為出廠壞區塊。
 *   - Factory Information 區域 (系統保留 Block) 會直接略過，不納入掃描。
 *   - 掃描結果會寫入 BBT_Table[]： true  → 壞區塊
 *     true  → 壞區塊
 *     false → 良好區塊
 *
 *  @return void
 */
void BBT_ScanFactoryBlocks(void)
{
	uint8_t Main0, Spare0;

	/// Step 1: 逐一掃描所有 Block
	for (uint32_t Block = 0; Block < TOTAL_BLOCKS; Block++)
	{
		/// Step 2: 跳過 Factory Information / 系統保留 Block
		if (Block < FACTORY_INFO_BLOCK_END || Block > FACTORY_INFO_BLOCK2_START)
		{
			BBT_Table[Block] = false;
			continue;
		}

		/// Step 3: 判斷是否為出廠壞區塊
		if (is_factory_bad(Block, &Main0, &Spare0))
		{
			BBT_Table[Block] = true;
			printf("[Invalid Block] = %lu (m:0x%02X s:0x%02X)\r\n", (unsigned long) Block, Main0,
			Spare0);
		}
		else
		{
			BBT_Table[Block] = false;
		}
	}
}

/** @brief 將 Block 標記為 Invalid Block
 *
 *  @details
 *   - 當 Block 發生 Program 或 Erase 失敗時呼叫
 *   - 此函式會同時：
 *   - 更新記憶體內的 BBT_Table[]
 *   - 將壞區塊標記（0x00）永久寫入 Page0 的 spare[0]
 *   - 確保該 Block 在後續配置中不再被使用
 *
 *  @param block : 欲標記為 Runtime 壞區塊的 Block 索引
 */
void BBT_MarkRuntimeBad(uint32_t Block)
{
	/// Step 1: 檢查 Block Index 合法性
	if (Block >= TOTAL_BLOCKS)
		return;

	/// Step 2: 若已為壞區塊，直接返回
	if (BBT_Table[Block])
		return;

	/// Step 3: 更新記憶體內 BBT Table
	BBT_Table[Block] = true;
	printf("[Invalid Table] Runtime Bad Block = %lu\r\n", (unsigned long) Block);

	/// Step 4: 將壞區塊標記永久寫入 Page0 的 spare[0]
	write_bad_marker_page0_spare0(Block);
}

/** @brief 查詢指定 Block 是否為壞區塊
 *
 *  @details
 *   - 透過查詢記憶體內的 BBT_Table[]，快速判斷 Block 狀態。
 *   - 在任何 Read / Program / Erase 操作前皆應呼叫此函式。
 *
 *  @param block : 目標 Block 索引
 *
 *  @return true   : Block 為壞區塊，不可使用
 *  @return false  : Block 為良好區塊，可正常使用
 */
bool BBT_IsBad(uint32_t Block)
{
	/// Step 1: 超出範圍的 Block 視為壞區塊
	if (Block >= TOTAL_BLOCKS)
		return true;

	/// Step 2: 回傳 BBT Table 中的狀態
	return BBT_Table[Block];
}

/** @brief 輸出 Invalid Block Message
 *
 *  @details
 *   - 統計 BBT_Table[] 中壞區塊與良好區塊的數量。
 *   - 用於除錯、驗證與生產測試階段。
 *
 *  @return void
 */
void BBT_PrintSummary(void)
{
	uint32_t Bad = 0;

	/// Step 1: 統計壞區塊數量
	for (uint32_t i = 0; i < TOTAL_BLOCKS; i++)
	{
		if (BBT_Table[i])
			Bad++;
	}

	/// Step 2: 輸出統計結果
	printf("[Invalid Table] Total = %d, Bad = %lu, Good = %lu\r\n",
	TOTAL_BLOCKS, (unsigned long) Bad, (unsigned long) (TOTAL_BLOCKS - Bad));
}

/** @brief 顯示目前 Bad Block Table (BBT) 中所有壞區塊的索引
 *
 *  @details
 *   - 逐一掃描記憶體內的 BBT_Table[]。
 *   - 若某 Block 被標記為壞區塊，則輸出其 Block Index。
 *   - 用於除錯或生產測試時觀察壞區塊分佈情況。
 *
 *  @return void
 */
void BBT_ShowBadBlock(void)
{
	for (uint32_t Block = 0; Block < TOTAL_BLOCKS; Block++)
	{
		if (BBT_Table[Block])
		{
			printf("[Invalid Table] Invalid Block = %lu\r\n", (unsigned long) Block);
		}
	}
}

/** @brief 將所有壞區塊索引收集至使用者提供的陣列中
 *
 *  @details
 *   - 掃描 BBT_Table[]，將所有被標記為壞區塊的 Block Index
 *     依序存入 list[]。
 *   - 若壞區塊數量超過 list[] 容量，仍會完整計數，
 *     但僅儲存前 maxlen 筆。
 *   - 此函式常用於 FTL、Wear-Leveling 或配置管理模組。
 *
 *  @param list   : [out] 用於存放壞區塊索引的陣列指標
 *  @param maxlen : list[] 可容納的最大元素數量
 *
 *  @return 壞區塊的總數（可能大於 maxlen）
 */
uint32_t BBT_GetBadBlocks(uint32_t *List, uint32_t Len)
{
	uint32_t Count = 0;

	for (uint32_t Block = 0; Block < TOTAL_BLOCKS; Block++)
	{
		if (BBT_Table[Block])
		{
			if (Count < Len)
				List[Count] = Block;
			Count++;
		}
	}
	return Count;
}

/** @brief 找出第一個 Valid Block 供系統使用
 *
 *  @details
 *   - 從 Block Index 8 開始掃描，以避開前段系統保留區。
 *   - 搜尋範圍截止於 Factory Information 保留區之前。
 *   - 回傳第一個未被標記為壞區塊的 Block。
 *
 *  @return    : 可用的 Block Index
 *  @return -1 : 找不到任何可用 Block
 */
int FindFirstValidBlock(void)
{
	for (int Block = 8; Block < FACTORY_INFO_BLOCK2_START; Block++)
	{
		if (!BBT_IsBad(Block))
		{
			return (int) Block;
		}
	}

	return -1;
}
