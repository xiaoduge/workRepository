/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_24LC01.h
** Descriptions:            APP_24LC01.c header File
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
#ifndef __APP_24LC01B_H
#define __APP_24LC01B_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
/* Pins Definition */
#define Pin_WP_24LC01B  GPIOB, GPIO_Pin_12
#define Pin_SCL_24LC01B GPIOB, GPIO_Pin_10
#define Pin_SDA_24LC01B GPIOB, GPIO_Pin_11
/* Pins Operation */
#define WP_24LC01B_Set    GPIO_SetBits(Pin_WP_24LC01B)
#define WP_24LC01B_Reset  GPIO_ResetBits(Pin_WP_24LC01B)

#define SCL_24LC01B_Set   GPIO_SetBits(Pin_SCL_24LC01B)
#define SCL_24LC01B_Reset GPIO_ResetBits(Pin_SCL_24LC01B)

#define SDA_24LC01B_Set   GPIO_SetBits(Pin_SDA_24LC01B)
#define SDA_24LC01B_Reset GPIO_ResetBits(Pin_SDA_24LC01B)
#define SDA_24LC01B       GPIO_ReadInputDataBit(Pin_SDA_24LC01B)
/* Operation Status */
#define _24LC01_Write 0
#define _24LC01_Read  1
/* Work Status */
#define _24LC01_Error 1
/* Public variable prototypes ------------------------------------------------*/
extern char RAM_24LC01B;
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_24LC01B(void);
extern char Operate_24LC01B(char, char, char);
#endif /* __APP_24LC01B_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
