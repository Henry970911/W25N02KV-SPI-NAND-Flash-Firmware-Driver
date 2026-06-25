/*
 * Nand_Dri_StatusRegister.c
 *
 *  Created on: Feb 27, 2026
 *      Author: User
 */

#include "Nand_Dri_StatusRegister.h"

uint8_t ReadStatusRegister(uint8_t SrAddr)
{
	uint8_t Command[2] =
	{ CMD_READ_SR, SrAddr };

	uint8_t Sr = 0;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 2);
	SPI_Receive(&Sr, 1);
	SPI_PULLUP();

	return Sr;
}

void WriteStatusRegister(uint8_t SrAddr, uint8_t Value)
{
	uint8_t Command[3] =
	{ CMD_WRITE_SR, SrAddr, Value };

	SPI_PULLDOWN();
	SPI_Transmit(Command, 3);
	SPI_PULLUP();
}
