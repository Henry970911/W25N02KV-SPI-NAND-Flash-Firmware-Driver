/*
 *  Test_Endurance.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include "Test_Endurance.h"

/** EnduranceTest_Run
 *
 *  @brief
 *   執行指定 NAND Block 的 P/E（Program / Erase）耐久度測試
 *
 *  @details
 *   - 本函式用於評估單一 Block 的耐久度（Endurance）
 *   - 每一個 P/E Cycle 依序執行：
 *     => Block Erase
 *     => 全 Block Page Program（Main Area）
 *     => Page Read + Data Verify
 *     => ECC 與 Status Register 檢查
 *   - 任一階段發生以下狀況即立即終止測試：
 *     => Erase Fail（E_FAIL）
 *     => Program Fail（P_FAIL）
 *     => ECC Uncorrectable Error
 *     => Read / Verify mismatch
 *
 *  @param block : 目標測試的 Logical Block Index
 *
 *  @return None 測試結果與進度資訊皆透過 Console Log 輸出
 *
 *  @note
 *   - Block Size = 128KB (64 Pages * 2KB Main Area)
 *   - 實際可承受 P/E Cycle 依 NAND Grade 而異（典型約 60K）
 *   - 測試過程會對 Block 進行完整破壞性寫入
 */
void EnduranceTest(uint32_t Block)
{
	bool verifyFail = false;
	uint8_t readBuffer[PAGE_MAIN_SIZE];
	uint8_t writeBuffer[PAGE_MAIN_SIZE];
	uint32_t base_page = Block * PAGES_PER_BLOCK;

	printf("==========================================================\r\n");
	printf("================ [Endurance Test Started] ================\r\n");
	printf("[Endurance Test] Block: %lu \r\n", Block);
	printf("[Endurance Test] Cycle: %d  \r\n", BLOCK_PE_CYCLES);

	/// Step 1:
	/// 軟體重置 NAND 並準備測試資料 Pattern
	/// - [66h + 99h] Software Reset
	/// - 清除 Status Register
	/// - 寫入 Pattern = 0xAA 至 writeBuffer
	SoftwareReset_Service();
	PreparePattern(writeBuffer, PAGE_MAIN_SIZE, PATTERN_AA);

	for (uint32_t cycle = 0; cycle < BLOCK_PE_CYCLES; cycle++)
	{
		/// Step 2:
		/// Block Erase
		/// - 指令：[D8h] Block Erase (128KB)
		/// - 等待完成並檢查 Erase Fail（SR2: E_FAIL）
		if (!BlockErase128K_service(Block, 500))
			printf("[Endurance Test] Cycle %lu Erase Failed\r\n", cycle);

		for (uint32_t page = 0; page < PAGES_PER_BLOCK; page++)
		{
			uint32_t page_addr = base_page + page;

			/// Step 3:
			/// Page Program（Main Area）
			/// - [06h] Write Enable
			/// - [02h] Program Load
			/// - [10h] Program Execute
			/// - 檢查 Program Fail（SR3: P_FAIL）
			if (!StandardProgram_Service(page_addr, writeBuffer, PAGE_MAIN_SIZE))
			{
				printf("[Endurance] Cycle %lu\r\n", cycle);
				printf("[Endurance] Page %lu Program Fail\r\n", page);
				verifyFail = true;
				break;
			}

			/// Step 4:
			/// Page Read + Data Verify
			/// - [13h] Page Data Read
			/// - [03h] Read From Cache
			/// - 檢查 ECC Status (Correctable / Uncorrectable)
			if (!StandardRead_Service(page_addr, 0x0000, readBuffer, PAGE_MAIN_SIZE))
			{
				printf("[Endurance] Cycle %lu\r\n", cycle);
				printf("[Endurance] Page %lu Read Failed\r\n", page);
				verifyFail = true;
				break;
			}

			/// Step 4-1:
			/// Byte-by-byte 資料比對 (Verify)
			for (int i = 0; i < PAGE_MAIN_SIZE; i++)
			{
				if (readBuffer[i] != writeBuffer[i])
				{
					printf("[Endurance] Verify Mismatch at Byte %d\r\n", i);
					printf("[Endurance] Exp : 0x%02X\r\n", writeBuffer[i]);
					printf("[Endurance] Got : 0x%02X\r\n", readBuffer[i]);
					verifyFail = true;
					break;
				}
			}

			if (verifyFail)
				break;
		}

		if (verifyFail)
			break;

		/// Step 5:
		/// 檢查 ECC 與 Status Registers
		/// - SR1 / SR2 / SR3
		/// - 若偵測到 E_FAIL / P_FAIL 或 ECC Uncorrectable 則終止測試
		ECC_Status_t ecc = GetECCStatus_service();
		uint8_t sr1 = GetSR1();
		uint8_t sr2 = GetSR2();
		uint8_t sr3 = GetSR3();

		printf("[Cycle %lu] SR1=0x%02X SR2=0x%02X SR3=0x%02X ECC=%d\r\n", cycle, sr1, sr2, sr3, ecc);

		if (CheckEraseFail_service() || CheckProgramFail_service())
		{
			printf("[Cycle %lu] EFAIL / PFAIL Detected\r\n", cycle);
			break;
		}

		if (ecc == ECC_UNCORRECTABLE)
		{
			printf("[Cycle %lu] ECC Uncorrectable -> End Test\r\n", cycle);
			break;
		}

		/// Step 6:
		/// 顯示測試進度 (每 100 cycles 輸出一次)
		if ((cycle + 1) % 100 == 0)
		{
			printf("[Progress] %lu cycles completed\r\n", cycle + 1);
		}
	}

	printf("=============== [Endurance Test Finished] ===============\r\n");
	printf("=========================================================\r\n");
}
