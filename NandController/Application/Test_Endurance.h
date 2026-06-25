/*
 *  Test_Endurance.h
 *
 *  Created on: Mar 2, 2026
 *  Author: Henry
 */

#ifndef APPLICATION_TEST_ENDURANCE_H_
#define APPLICATION_TEST_ENDURANCE_H_

#include "Test_Pattern.h"
#include "BBT_Services.h"
#include "Read_Services.h"
#include "Reset_Services.h"
#include "W25N02KV_Config.h"
#include "Program_Services.h"
#include "BlockErase_Services.h"

void EnduranceTest(uint32_t Block);

#endif /* APPLICATION_TEST_ENDURANCE_H_ */
