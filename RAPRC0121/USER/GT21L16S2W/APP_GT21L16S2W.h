/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_GT21L16S2W.h
** Descriptions:            APP_GT21L16S2W.c header File
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-6-16
** Version:                 V 0.0.1
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __APP_GT21L16S2W_H
#define __APP_GT21L16S2W_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
/* Pins Definition */
#define Pin_SPI_NSS_GT21L16S2W  GPIOA, GPIO_Pin_4
#define Pin_SPI_SCK_GT21L16S2W  GPIOA, GPIO_Pin_5
#define Pin_SPI_MISO_GT21L16S2W GPIOA, GPIO_Pin_6
#define Pin_SPI_MOSI_GT21L16S2W GPIOA, GPIO_Pin_7
/* Pins Operation */
#define SPI_NSS_GT21L16S2W_Set    GPIO_SetBits(Pin_SPI_NSS_GT21L16S2W)
#define SPI_NSS_GT21L16S2W_Reset  GPIO_ResetBits(Pin_SPI_NSS_GT21L16S2W)

#define SPI_SCK_GT21L16S2W_Set    GPIO_SetBits(Pin_SPI_SCK_GT21L16S2W)
#define SPI_SCK_GT21L16S2W_Reset  GPIO_ResetBits(Pin_SPI_SCK_GT21L16S2W)

#define SPI_MISO_GT21L16S2W       GPIO_ReadInputDataBit(Pin_SPI_MISO_GT21L16S2W)

#define SPI_MOSI_GT21L16S2W_Set   GPIO_SetBits(Pin_SPI_MOSI_GT21L16S2W)
#define SPI_MOSI_GT21L16S2W_Reset GPIO_ResetBits(Pin_SPI_MOSI_GT21L16S2W)
/* Word No Definition */
#define __6X12_  0
#define __11X12_ 1
/* Public variable prototypes ------------------------------------------------*/
extern char Ram_6X12_GT21L16S2W[12];
extern char Ram_11X12_GT21L16S2W[22];
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_GT21L16S2W(void);
extern void Read_GB2312_6X12_GT21L16S2W(int);
extern void Read_GB2312_11X12_GT21L16S2W(int);
#endif /* __APP_GT21L16S2W_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
