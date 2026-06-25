/*
 *  OTP_Services.c
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#include "OTP_Services.h"

/** OTP_ReadPage
 *
 *  @brief  讀取指定的 OTP（One-Time Programmable）頁面資料
 *
 *  @details
 *   - 在暫時啟用 OTP 存取模式下，執行完整的 OTP 頁面讀取流程
 *   - OTP 區域共包含 12 個頁面（0x00–0x0B），其固定對應如下：
 *   - Page 0x00：晶片出廠唯一識別碼（Factory Unique ID）
 *   - Page 0x01：參數／組態資料
 *   - Page 0x02–0x0B：使用者可讀寫頁面
 *   - 讀取操作不會改變 OTP 內容，可重複執行
 *
 *  @param otp_page_index : 目標 OTP 頁面索引（0x00–0x0B）
 *  @param buf            : [out] 用於接收資料的緩衝區指標
 *  @param len            : 欲讀取的資料長度（Bytes）
 *
 *  @return true   : OTP 頁面讀取完成且成功
 *  @return false  : 頁面索引不合法或讀取流程失敗
 */
bool OTP_ReadPage(uint8_t OTP_PageIndex, uint8_t *Buffer, uint16_t Len)
{
	if (OTP_PageIndex > OTP_PAGE_MAX)
		return false;

	/// Step 1: 進入 OTP 模式
	if (!OTPEnable_Service(true))
		return false;

	uint32_t PageAddr = OTP_PageIndex;

	/// Step 2: PageDataRead (13h)，將 OTP Page 載入 Cache
	PageDataRead(PageAddr);

	/// Step 3: 等待裝置就緒 (Polling OIP)
	if (!IsBusyWithTimeout_service(100))
		return false;

	/// Step 4: ReadData (03h)，從 Cache 讀取資料
	ReadData(0x0000, Buffer, Len);

	/// Step 5: 離開 OTP 模式
	OTPEnable_Service(false);

	return true;
}

/** OTP_ProgramPage
 *
 *  @brief  將使用者資料寫入指定的 OTP（One-Time Programmable）頁面
 *
 *  @details
 *   - 在啟用 OTP 模式下，執行完整的 OTP 程式寫入流程
 *   - 僅允許頁面 0x02–0x0B 進行使用者資料寫入；
 *     頁面 0x00 與 0x01 為出廠保留頁面，不可寫入
 *   - OTP 頁面一旦寫入後即無法修改或抹除
 *
 *  @param otp_page_index : 目標 OTP 頁面索引（0x02–0x0B）
 *  @param buf            : [in] 指向欲寫入資料的緩衝區指標
 *  @param len            : 欲寫入的資料長度（Bytes）
 *
 *  @return true   : OTP 頁面寫入成功
 *  @return false  : 頁面索引不合法、發生逾時或寫入失敗
 */
bool OTP_ProgramPage(uint8_t OTP_PageIndex, const uint8_t *Buffer, uint16_t Len)
{
	if (OTP_PageIndex < OTP_PAGE0 || OTP_PageIndex > OTP_PAGE_MAX)
		return false;

	/// Step 1: 進入 OTP 模式
	if (!OTPEnable_Service(true))
		return false;

	uint32_t PageAddr = OTP_PageIndex;

	/// Step 2: LoadProgramData (02h)，將資料載入 Page Buffer
	LoadProgramData(0x0000, (uint8_t*) Buffer, Len);

	/// Step 3: ProgramExecute (10h)，將 Buffer 資料寫入 OTP Page
	ProgramExecute(PageAddr);

	/// Step 4: 等待程式寫入完成（Polling OIP）
	if (!IsBusyWithTimeout_service(100))
		return false;

	/// Step 5: 離開 OTP 模式
	OTPEnable_Service(false);

	return true;
}
