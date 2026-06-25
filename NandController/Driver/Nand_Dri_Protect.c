/*
 *  Nand_Dri_Protect.C
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#include "Nand_Dri_Protect.h"

void WriteEnable(void)
{
	uint8_t Command = CMD_WRITE_ENABLE;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_PULLUP();
}

void WriteDisable(void)
{
	uint8_t Command = CMD_WRITE_DISABLE;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_PULLUP();
}
