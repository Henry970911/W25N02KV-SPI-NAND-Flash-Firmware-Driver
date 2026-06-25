/*
 *  Nand_Dri_Read.c
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#include "Nand_Dri_Read.h"

void PageDataRead(uint32_t PageAddr)
{
	uint8_t Command[4];

	Command[0] = CMD_PAGE_DATA_READ;
	Command[1] = (PageAddr >> 16) & 0xFF;
	Command[2] = (PageAddr >> 8) & 0xFF;
	Command[3] = (PageAddr >> 0) & 0xFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_PULLUP();
}

void ReadData(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_READ_DATA;
	Command[1] = (ColAddr >> 8) & 0xFF; /// CA[15:8]
	Command[2] = (ColAddr >> 0) & 0xFF; /// CA[7:0]
	Command[3] = 0x00; 					/// Dummy byte (8 clocks)

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastRead(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadWith4ByteAddr(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_WITH_4BYTE_ADDRESS;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadDualOutput(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_DUAL_OUTPUT;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadDualOutputWith4ByteAddr(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_DUAL_OUTPUT_4BYTE;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadQuadOutput(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_QUAD_OUTPUT;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadQuadOutputWith4ByteAddr(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_QUAD_OUTPUT_4BYTE;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadDualIO(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_DUAL_IO;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadDualIOWith4ByteAddr(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_DUAL_IO_4BYTE;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadQuadIO(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_QUAD_IO;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}

void FastReadQuadIOWith4ByteAddr(uint16_t ColAddr, uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[4];

	Command[0] = CMD_FAST_READ_QUAD_IO_4BYTE;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = (ColAddr >> 0) & 0xFF;
	Command[3] = 0x00;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_Receive(Buf, Len);
	SPI_PULLUP();
}
