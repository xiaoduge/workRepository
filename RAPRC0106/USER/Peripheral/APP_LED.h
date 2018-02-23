/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               LED.h
** Descriptions:            LED.c header File
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-7-15
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
#ifndef __APP_LED_H
#define __APP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
#define Pin_LED1_Green GPIOA, GPIO_Pin_0//1-G
#define Pin_LED1_Red   GPIOA, GPIO_Pin_1//1-R
#define Pin_LED2_Green GPIOA, GPIO_Pin_2//2-G
#define Pin_LED2_Red   GPIOA, GPIO_Pin_3//2-R
/* Pins Operation */
#define LED1_G_Off GPIO_SetBits(Pin_LED1_Green)
#define LED1_G_On  GPIO_ResetBits(Pin_LED1_Green)

#define LED1_R_Off GPIO_SetBits(Pin_LED1_Red)
#define LED1_R_On  GPIO_ResetBits(Pin_LED1_Red)

#define LED2_G_Off GPIO_SetBits(Pin_LED2_Green)
#define LED2_G_On  GPIO_ResetBits(Pin_LED2_Green)

#define LED2_R_Off GPIO_SetBits(Pin_LED2_Red)
#define LED2_R_On  GPIO_ResetBits(Pin_LED2_Red)
/* Change */
#define LED_Power_Off   LED1_G_Off
#define LED_Power_On    LED1_G_On

#define LED_Operate_Off LED2_G_Off
#define LED_Operate_On  LED2_G_On

#define LED_Error_Off   LED2_R_Off
#define LED_Error_On    LED2_R_On
/* Public variable prototypes ------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
extern void Initialize_LED(void);
#endif /* __APP_LED_H */

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
