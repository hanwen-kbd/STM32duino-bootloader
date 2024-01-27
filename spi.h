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

#include "common.h"

typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 SR;
  u16  RESERVED2;
  vu16 DR;
  u16  RESERVED3;
  vu16 CRCPR;
  u16  RESERVED4;
  vu16 RXCRCR;
  u16  RESERVED5;
  vu16 TXCRCR;
  u16  RESERVED6;
  vu16 I2SCFGR;
  u16  RESERVED7;
  vu16 I2SPR;
  u16  RESERVED8;  
} SPI_TypeDef;

typedef struct
{
  u16 SPI_Direction;
  u16 SPI_Mode;
  u16 SPI_DataSize;
  u16 SPI_CPOL;
  u16 SPI_CPHA;
  u16 SPI_NSS;
  u16 SPI_BaudRatePrescaler;
  u16 SPI_FirstBit;
  u16 SPI_CRCPolynomial;
} SPI_InitTypeDef;

#define SPI2_BASE   ((u32)0x40013800)
#define SPI2        ((SPI_TypeDef *) SPI1_BASE)
EXT SPI_TypeDef     *SPI2;

#define SPI_Direction_1Line_Rx    ((u16)0x8000)
#define SPI_Mode_Master           ((u16)0x0104)
#define SPI_DataSize_8b           ((u16)0x0000)
#define SPI_CPOL_Low              ((u16)0x0000)
#define SPI_CPHA_1Edge            ((u16)0x0000)
#define SPI_NSS_Soft              ((u16)0x0200)
#define SPI_BaudRatePrescaler_2   ((u16)0x0000)
#define SPI_FirstBit_MSB          ((u16)0x0000)

#define SPI_SPE   ((u16)0b1000000)

void setupSPI();
void disableSPI();
void SPI_transmit(u8 *data, u16 size);
