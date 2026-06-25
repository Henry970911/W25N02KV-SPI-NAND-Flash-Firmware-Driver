/*
 *  BBT_Services.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef SERVICES_BBT_SERVICES_H_
#define SERVICES_BBT_SERVICES_H_

#include "Read_Services.h"
#include "W25N02KV_Config.h"
#include "ReadID_Services.h"
#include "Nand_Dri_Program.h"
#include "Protect_Services.h"
#include "Program_Services.h"

extern bool BBT_Table[TOTAL_BLOCKS];

typedef struct
{
	uint16_t block_num; /// Block 編號
	uint8_t ecc_status; /// 紀錄 ECC 狀態
	uint8_t is_bad;     /// 是否為 Invalid Block
} Invalid_Block;

void BBT_ScanFactoryBlocks(void);
void BBT_MarkRuntimeBad(uint32_t Block);
bool BBT_IsBad(uint32_t Block);
void BBT_PrintSummary(void);
void BBT_ShowBadBlock(void);
uint32_t BBT_GetBadBlocks(uint32_t *List, uint32_t Len);
int FindFirstValidBlock(void);

static inline bool BBT_BadBlock(uint32_t Block)
{
	return (Block >= TOTAL_BLOCKS) ? true : BBT_Table[Block];
}

#endif /* SERVICES_BBT_SERVICES_H_ */
