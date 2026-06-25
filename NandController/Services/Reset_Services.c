/*
 *  Reset_Services.c
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#include "Reset_Services.h"

/**
 * @brief DeviceReset_Services
 *
 * @detail
 * - 此為「裝置層級」的 Reset 操作，通常對應硬體或裝置專用的 Reset 指令。
 * - Reset 後，NAND Flash 會回到上電後的初始狀態：
 * - 操作狀態清除
 * - Busy 狀態解除
 * - 內部狀態機重新初始化
 * - 不依賴 Reset Enable 指令, 可直接執行
 */
bool DeviceReset_Services(void)
{
	DeviceReset();

	printf(" [Device Reset] Sucsess\r\n");

	return true;
}

/**
 * @brief SoftwareReset_Service
 *
 * @detail
 * - Reset 行為由軟體指令觸發, 通常用於:
 *   => 操作異常後的狀態回復, 不影響整體硬體環境的情況下重置裝置
 * - Specification Flow:
 * 	 1.Enable Reset
 *   2.Reset
 */
bool SoftwareReset_Service(void)
{
	EnableReset();
	Reset();

	printf("[Software Reset] Success\r\n");

	return true;
}
