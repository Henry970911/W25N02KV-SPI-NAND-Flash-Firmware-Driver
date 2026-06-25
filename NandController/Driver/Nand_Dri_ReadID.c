/*
 *  Nand_ReadID.c
 *
 *  Created on: Feb 25, 2026
 *  Author: Henry
 */

#include <Nand_Dri_ReadID.h>

void W25N02KV_ReadJEDECID(uint8_t *Buf)
{
	uint8_t Command = JEDECID;
	uint8_t Dummy = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(&Command, 1);
	SPI_Transmit(&Dummy, 1);
	SPI_Receive(Buf, 3);
	SPI_PULLUP();
}
