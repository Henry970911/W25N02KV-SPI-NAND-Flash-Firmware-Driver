/*
 *  Nand_Dri_Reset.c
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#include "Nand_Dri_Reset.h"

void Reset(void)
{
	uint8_t Command = CMD_RESET;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_PULLUP();
}

void EnableReset(void)
{
	uint8_t Command = CMD_ENABLE_RESET;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_PULLUP();
}

void DeviceReset(void)
{
	uint8_t Command = CMD_DEVICE_RESET;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_PULLUP();
}
