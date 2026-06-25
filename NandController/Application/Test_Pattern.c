/*
 *  Test_Pattern.c
 *
 *  Created on: Mar 2, 2026
 *  Author: CPC
 */

#include "Test_Pattern.h"

void PreparePattern(uint8_t *Buffer, uint32_t Len, PatternType Type)
{
	switch (Type)
	{
	case PATTERN_AA:
		memset(Buffer, 0xAA, Len);
		break;

	case PATTERN_55:
		memset(Buffer, 0x55, Len);
		break;

	case PATTERN_FF:
		memset(Buffer, 0xFF, Len);
		break;

	case PATTERN_00:
		memset(Buffer, 0x00, Len);
		break;

	case PATTERN_ALT_AA55:
		for (uint32_t i = 0; i < Len; i++)
			Buffer[i] = (i % 2 == 0) ? 0xAA : 0x55;
		break;

	case PATTERN_SEQ_AA55FF00:
	{
		uint8_t Sequence[] =
		{ 0xAA, 0x55, 0xFF, 0x00 };
		for (uint32_t i = 0; i < Len; i++)
			Buffer[i] = Sequence[i % 4];
		break;
	}

	case PATTERN_PRBS:
	{
		uint32_t LFSR = 0xACE1u; // 初始種子，可修改
		for (uint32_t i = 0; i < Len; i++)
		{
			// LFSR (x^16 + x^14 + x^13 + x^11) 多項式
			LFSR = (LFSR >> 1) ^ (-(int32_t) (LFSR & 1u) & 0xB400u);
			Buffer[i] = (uint8_t) LFSR;
		}
		break;
	}

	default:
		memset(Buffer, 0x00, Len);
		break;
	}
}
