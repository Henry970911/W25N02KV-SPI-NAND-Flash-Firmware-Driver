/*
 *  Program_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */
#include "Program_Services.h"

/** StandardProgram_Service
 *
 *  @brief 執行標準頁面程式寫入 (Standard Page Program)
 *
 *  @details
 *   - 寫單一完整頁面, 每次操作對應一個 Page (2 KB)
 *   - 從 Column Address = 0x0000 位址寫入, 適用於主資料區(Main Area)
 *
 *  @param page_addr : Target Page Address
 *  @param buf       : [in] 欲寫入資料
 *  @param len       : 資料長度(Bytes)
 *
 *  @return true   : 寫入成功 (未逾時且 P_FAIL = 0)
 *  @return false  : 寫入失敗或發生逾時
 */
bool StandardProgram_Service(uint32_t PageAddr, const uint8_t *Buffer, uint16_t Len)
{
	/// Step 1: Write Enable
	if (!WriteEnable_Services())
		return false;

	/// Step 2: 將資料從 Column=0x0000 開始載入 Page Buffer
	/// Step 3: 執行 Program Execute，把 Buffer 資料寫進 NAND Page
	LoadProgramData(0x0000, Buffer, Len);
	ProgramExecute(PageAddr);

	/// Step 4: 等待程式完成 (Polling SR3 OIP bit)
	if (!IsBusyWithTimeout_service(100))
		return false;

	/// Step 5: 檢查 Program Fail (P_Fail=1 代表失敗)
	if (CheckProgramFail_service() == true)
	{
		printf("[Standard Program] Failed (P_Fail = 1)\r\n");
		return false;
	}
	else
	{
		printf("[Standard Program] Success (P_Fail = 0)\r\n");
		return true;
	}
}

/** RandomProgram_Service
 *
 *  @brief 執行隨機欄位程式寫入 (Random Page Program)
 *
 *  @details
 *   - 允許從指定的 Column Address 開始，覆寫 Page Buffer 內的資料
 *   - 更新頁面 Page Buffer 的資料(例如 Spare Area、OOB 或 Metadata)
 *
 *  @param page_addr : Target Page Address
 *  @param col_addr  : 頁面內的欄位起始位址 (Column Address)
 *  @param buf       : [in] 指向欲寫入資料的緩衝區指標
 *  @param len       : 資料長度(Bytes)
 *
 *  @return true   : 隨機程式寫入成功（未逾時且 P_FAIL = 0）
 *  @return false  : 程式寫入失敗或發生逾時
 */
bool RandomProgram_Service(uint32_t PageAddr, uint16_t ColAddr, const uint8_t *Buffer, uint16_t Len)
{
	/// Step 1: Write Enable
	if (!WriteEnable_Services())
		return false;

	/// Step 2: 載入資料到 Page Buffer (可多次呼叫 0x84，更新不同 col_addr)
	/// Step 3: 執行 Program Execute，把整個 Page Buffer 寫進 NAND
	RandomLoadProgramData(ColAddr, Buffer, Len);
	ProgramExecute(PageAddr);

	/// Step 4: 等待程式完成 (Polling SR3 OIP bit)
	IsBusyWithTimeout_service(100);

	/// Step 5: 檢查 Program Fail (P_Fail = 1)
	if (CheckProgramFail_service())
	{
		printf("[Random Program] Failed (P_Fail = 1)\r\n");
		return false;
	}
	else
	{
		printf("[Random Program] Success (P_Fail = 0)\r\n");
		return true;
	}
}
