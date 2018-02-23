/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_SN74ALVC164245.h
** Descriptions:            APP_SN74ALVC164245.c header File
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-2-11
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
#ifndef __APP_SN74ALVC164245_H
#define __APP_SN74ALVC164245_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
#define SN74ALVC164245_2DIR GPIOC, GPIO_Pin_8

#define SN74ALVC164245_1A1 GPIOA, GPIO_Pin_12
#define SN74ALVC164245_1A2 GPIOB, GPIO_Pin_0
#define SN74ALVC164245_1A3 GPIOB, GPIO_Pin_1
#define SN74ALVC164245_1A4 GPIOB, GPIO_Pin_2
#define SN74ALVC164245_1A5 GPIOB, GPIO_Pin_5
#define SN74ALVC164245_1A6 GPIOB, GPIO_Pin_8
#define SN74ALVC164245_1A7 GPIOB, GPIO_Pin_9
#define SN74ALVC164245_1A8 GPIOD, GPIO_Pin_2

#define SN74ALVC164245_2A1 GPIOC, GPIO_Pin_0
#define SN74ALVC164245_2A2 GPIOC, GPIO_Pin_1
#define SN74ALVC164245_2A3 GPIOC, GPIO_Pin_2
#define SN74ALVC164245_2A4 GPIOC, GPIO_Pin_3
#define SN74ALVC164245_2A5 GPIOC, GPIO_Pin_4
#define SN74ALVC164245_2A6 GPIOC, GPIO_Pin_5
#define SN74ALVC164245_2A7 GPIOC, GPIO_Pin_6
#define SN74ALVC164245_2A8 GPIOC, GPIO_Pin_7
/* Public function prototypes ------------------------------------------------*/
void Initialize_SN74ALVC164245(void);
#endif /* __APP_SN74ALVC164245_H */

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
