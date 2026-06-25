/*
 *  Nand_Dri_Program.c
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#include "Nand_Dri_Program.h"

/**
 *  @brief LoadProgramData
 *
 *  @detail
 *  - 將欲寫入資料透過 CMD 送進 SPI NAND 的 Catch Buffer
 *  - 等待 Program Execute CMD, 寫進 SPI NAND 中
 */
void LoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[3];

	Command[0] = CMD_LOAD_PROGRAM_DATA;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = ColAddr & 0xFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 3);
	SPI_Transmit(Buf, Len);
	SPI_PULLUP();
}

/**
 *  @brief RandomLoadProgramData
 *
 *  @detail
 *  - 什麼是 RandomLoadProgram ???
 *  - 和 LoadProgram 差別在哪裡 ???
 */
void RandomLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[3];

	Command[0] = CMD_RANDOM_LOAD_PROGRAM_DATA;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = ColAddr & 0XFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 3);
	SPI_Transmit(Buf, Len);
	SPI_PULLUP();
}

void QuadLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[3];

	Command[0] = CMD_QUAD_LOAD_PROGRAM_DATA;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = ColAddr & 0xFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 3);
	SPI_Transmit(Buf, Len);
	SPI_PULLUP();
}

void QuadRandomLoadProgramData(uint16_t ColAddr, const uint8_t *Buf, uint16_t Len)
{
	uint8_t Command[3];

	Command[0] = CMD_QUAD_RANDOM_LOAD_PROGRAM_DATA;
	Command[1] = (ColAddr >> 8) & 0xFF;
	Command[2] = ColAddr & 0xFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 3);
	SPI_Transmit(Buf, Len);
	SPI_PULLUP();
}

void ProgramExecute(uint32_t PageAddr)
{
	uint8_t Command[4];

	Command[0] = CMD_PROGRAM_EXECUTE;
	Command[1] = (PageAddr >> 16) & 0xFF;
	Command[2] = PageAddr >> 8 & 0xFF;
	Command[3] = PageAddr & 0xFF;

	SPI_PULLDOWN();
	SPI_Transmit(Command, 4);
	SPI_PULLUP();
}
