/*
 *  Read_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include "Read_Services.h"

/** StandardRead_Service
 *
 *  @brief  執行標準頁面讀取操作 (13h + 03h)
 *
 *  @details
 *   - NAND Array 中讀取完整頁面或主要資料區 (Main Area)
 *   - 讀取完成後進行 ECC 狀態檢查與錯誤分類
 *   - 呼叫前需確保 SR2 ECC 功能是否啟用 (SR2 鎖定時無法讀取資料)
 *   - 典型頁面讀取延遲時間 tR 約為 25–50 µs（依資料手冊定義）。
 *
 *  @param page_addr : Target Page Address
 *  @param col_addr  : Page 欄位起始位址 (Column Address) - 0x0000:主資料區 (Main Area)
 *  @param buf [out] : 接收資料的 Buffer
 *  @param len       : 資料長度(Bytes)
 *
 *  @return true  : Read Success
 *  @return false : Time or ECC Failed
 */
bool StandardRead_Service(uint32_t PageAddr, uint16_t ColAddr, uint8_t *Buffer, uint16_t Len)
{
	PageDataRead(PageAddr);

	if (!IsBusyWithTimeout_service(100))
	{
		printf("[Read] Timeout... Status is Busy.\r\n");
		return false;
	}

	ReadData(ColAddr, Buffer, Len);

	ECC_Status_t ecc = GetECCStatus_service();

	/// ECC Status check
	switch (ecc)
	{
	case ECC_SUCCESS:
		printf("[Status] ECC_SUCCESS (Page = 0x%05X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_SUCCESS_CORRECTED:
		printf("[Status] ECC_SUCCESS_CORRECTED (Page = 0x%05X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_CORRECTED_THRESHOLD:
		printf("[Status] ECC_CORRECTED_THRESHOLD (Page = 0x%05X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_UNCORRECTABLE:
		printf("[Status] ECC_UNCORRECTABLE (Page = 0x%05X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;
	default:
		printf("[Status] ECC_RESERVED  (Page = 0x%05X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		return false;
	}
	return true;
}

/** RandomRead_Service
 *
 *  @brief  執行隨機欄位讀取操作（13h + 03h，自訂 Column Address）
 *
 *  @details
 *   - 從指定頁面中的特定欄位位址讀取部分資料。
 *   - 常用於讀取 Spare Area、Metadata 或頁面內部特定位元組區段。
 *   - 讀取完成後會進行 ECC 狀態檢查與結果分類。
 *
 *  Command Flow：
 *   1. [13h + PA2:PA1:PA0] PageDataRead → 將目標頁面載入 Cache
 *   2. 等待 OIP = 0（SR3[0]）→ 裝置就緒
 *   3. [03h + CA1:CA0] ReadData → 從指定欄位位址讀取資料
 *   4. 透過 GetECCStatus_service() 進行 ECC 狀態檢查
 *
 *  @param page_addr 目標頁面位址（Page Address）
 *  @param col_addr
 *         欄位位址（Column Address）
 *         - 範圍：0x0000–0x083F（Main / Spare Area）
 *
 *  @param buf
 *         [out] 用於接收資料的緩衝區指標
 *
 *  @param len
 *         欲讀取的資料長度（Bytes）
 *
 *  @return true
 *          讀取成功（ECC 正常或已修正）
 *
 *  @return false
 *          逾時（Timeout）或發生不可修正的 ECC 錯誤
 */
bool RandomRead_Service(uint32_t PageAddr, uint16_t ColAddr, uint8_t *Buffer, uint16_t Len)
{
	/// Step 1: PageDataRead (0x13)
	PageDataRead(PageAddr);

	/// Step 2: 等待 NAND Ready
	if (!IsBusyWithTimeout_service(100))
	{
		printf("[Random Read] Timeout ~ NAND Still Busy.\r\n");
		return false;
	}

	/// Step 3: ReadData with custom col_addr
	ReadData(ColAddr, Buffer, Len);

	ECC_Status_t ecc = GetECCStatus_service();

	/// ECC Status check
	switch (ecc)
	{
	case ECC_SUCCESS:
		printf("[Status] ECC_SUCCESS (Page = 0x%08X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_SUCCESS_CORRECTED:
		printf("[Status] ECC_SUCCESS_CORRECTED (Page = 0x%08X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_CORRECTED_THRESHOLD:
		printf("[Status] ECC_CORRECTED_THRESHOLD (Page = 0x%08X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		break;

	case ECC_UNCORRECTABLE:
	default:
		printf("[Status] ECC_UNCORRECTABLE (Page = 0x%08X Col = 0x%04X Len = %u)\r\n", (unsigned int) PageAddr, (unsigned int) ColAddr, (unsigned int) Len);
		return false;
	}

	return true;
}
