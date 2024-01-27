/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2024 Palette [@palette-dev]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

/**
 *  @file spi.c
 *
 *  @brief SPI stuff used by the WS2812 LEDs.
 *
 */
#include "common.h"
#include "spi.h"
#include "hardware.h"

void setupSPI() {
    u16 tmpreg = SPI2->CR1;
    tmpreg &= ((u16)0x3040)
    tmpreg |= (u16)((u32)SPI_Direction_1Line_Rx | SPI_Mode_Master |
                  SPI_DataSize_8b | SPI_CPOL_Low |  
                  SPI_CPHA_1Edge | SPI_NSS_Soft |  
                  SPI_BaudRatePrescaler_2 | SPI_FirstBit_MSB);
    SPI2->CR1 = tmpreg;
    SPI2->I2SCFGR &= ((u16)0xF7FF);
    SPI2->CR2 = 0;
    SPI2->DR = 0;
    SPI2->CR1 |= SPI_SPE;
}

void disableSPI() {
    SPI2->CR1 &= ~(SPI_SPE);
}

void SPI_transmit(u8 *data, u16 size) {
    for (u16 i = 0; i < size; i++) {
        while (!((SPI2->SR)&(0b10)));
        SPI2->DR = data[i];
    }
    while (!((SPI2->SR)&(0b10)));
    while (((SPI2->SR)&(0b10000000)));
    u16 temp = SPI2->DR;
	temp = SPI2->SR;
}
