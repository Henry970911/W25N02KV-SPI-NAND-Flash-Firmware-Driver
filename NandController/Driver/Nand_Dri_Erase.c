/*
 *  Nand_Dri_Erase.c
 *
 *  Created on: Feb 27, 2026
 *  Author: User
 */

#include "Nand_Dri_Erase.h"

void BlockErase(uint32_t BlockAddr)
{
	uint8_t Command[4];

	Command[0] = CMD_EraseBy128K;
	Command[1] = ((BlockAddr >> 16) & 0xFF);
	Command[2] = ((BlockAddr >> 8) & 0xFF);
	Command[3] = ((BlockAddr >> 0) & 0xFF);

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_PULLUP();
}
