/*
 *  nand_hal.h
 *
 *  Created on: Feb 25, 2026
 *  Author: Henry
 */

#ifndef HAL_NAND_HAL_H_
#define HAL_NAND_HAL_H_

#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32h7xx_hal.h"

extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi5;

void SPI_PULLUP(void);
void SPI_PULLDOWN(void);
void SPI_Transmit(const uint8_t *Data, uint16_t Len);
void SPI_Receive(uint8_t *Data, uint16_t Len);

#endif /* HAL_NAND_HAL_H_ */
