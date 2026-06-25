/*
 *  ReadID_Services.c
 *
 *  Created on: Mar 1, 2026
 *  Author: Henry
 */

#include "ReadID_Services.h"

void Read_JEDECID(void)
{
	uint8_t ID[3] =
	{ 0 };

	W25N02KV_ReadJEDECID(ID);

	printf(" [Read JEDEC ID] %02X %02X %02X\r\n", ID[0], ID[1], ID[2]);
}
