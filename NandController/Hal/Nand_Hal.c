/*
 *  nand_hal.c
 *
 *  Created on: Feb 25, 2026
 *  Author: Henry
 */

#include <Nand_Hal.h>

/**
 *  @brief SPI_PULLUP
 *
 *  @detail
 *	- SPI_NSS (CS) 手動控制, 拉高時結束通訊
 */
void SPI_PULLUP(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
}

/**
 *  @brief SPI_PULLDOWN
 *
 *  @detail
 *	- SPI_NSS (CS) 手動控制, 拉低時, STM32 當 Master, 開始進行通訊
 */
void SPI_PULLDOWN(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
}

/**
 *  @brief SPI_Transmit
 */
void SPI_Transmit(const uint8_t *Data, uint16_t Len)
{
	HAL_SPI_Transmit(&hspi5, Data, Len, 100);
}

/**
 *  @brief SPI_Receive
 */
void SPI_Receive(uint8_t *Data, uint16_t Len)
{
	HAL_SPI_Receive(&hspi5, Data, Len, 100);
}
