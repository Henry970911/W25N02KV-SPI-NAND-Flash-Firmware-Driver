/*
 *  Test_FactoryInvalidBlockScan.h
 *
 *  Created on: Mar 2, 2026
 *  Author: CPC
 */

#ifndef APPLICATION_TEST_FACTORYINVALIDBLOCKSCAN_H_
#define APPLICATION_TEST_FACTORYINVALIDBLOCKSCAN_H_

#include "Test_Pattern.h"
#include "BBT_Services.h"
#include "Read_Services.h"
#include "Reset_Services.h"
#include "W25N02KV_Config.h"
#include "Program_Services.h"
#include "BlockErase_Services.h"

void ScanInvaliBlocks(void);
void ChoseValidBlock(void);
void Standard_UnitTest(uint32_t BlockNum);

#endif /* APPLICATION_TEST_FACTORYINVALIDBLOCKSCAN_H_ */
