/*
 *  Test_SinglePage(RandomLoadProgram).h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef APPLICATION_TEST_SINGLEPAGE_RANDOMLOADPROGRAM__H_
#define APPLICATION_TEST_SINGLEPAGE_RANDOMLOADPROGRAM__H_

#include "W25N02KV_Config.h"
#include "Test_Pattern.h"
#include "BBT_Services.h"
#include "Reset_Services.h"
#include "Program_Services.h"
#include "BlockErase_Services.h"
#include "Read_Services.h"

void RandomLoadProgramTest(uint32_t BlockNum);

#endif /* APPLICATION_TEST_SINGLEPAGE_RANDOMLOADPROGRAM__H_ */
