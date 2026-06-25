/*
 *  Test_Pattern.h
 *
 *  Created on: Mar 2, 2026
 *  Author: CPC
 */

#ifndef APPLICATION_TEST_PATTERN_H_
#define APPLICATION_TEST_PATTERN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "W25N02KV_Config.h"

typedef enum
{
	PATTERN_AA,
	PATTERN_55,
	PATTERN_FF,
	PATTERN_00,
	PATTERN_ALT_AA55,
	PATTERN_SEQ_AA55FF00,
	PATTERN_PRBS
} PatternType;

void PreparePattern(uint8_t *Buffer, uint32_t Len, PatternType Type);

#endif /* APPLICATION_TEST_PATTERN_H_ */
