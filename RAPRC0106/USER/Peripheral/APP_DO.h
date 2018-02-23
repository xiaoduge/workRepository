/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_DO.h
** Descriptions:            APP_DO.c header File
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
#ifndef __APP_DO_H
#define __APP_DO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
/* Pins Definition */
#define Pin_DO1 GPIOC, GPIO_Pin_10
#define Pin_DO2 GPIOC, GPIO_Pin_9
/* Pins Operation */
#define DO1_Set   GPIO_SetBits(Pin_DO1)
#define DO1_Reset GPIO_ResetBits(Pin_DO1)

#define DO2_Set   GPIO_SetBits(Pin_DO2)
#define DO2_Reset GPIO_ResetBits(Pin_DO2)
/* Public variable prototypes ------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_DO(void);
#endif /* __APP_DO_H */

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
