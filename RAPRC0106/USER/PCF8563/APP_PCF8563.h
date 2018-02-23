/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_PCF8563.h
** Descriptions:            APP_PCF8563.c header File
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
#ifndef __APP_PCF8563_H
#define __APP_PCF8563_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
/* Pins Definition */
#define Pin_SCL_PCF8563 GPIOB, GPIO_Pin_6
#define Pin_SDA_PCF8563 GPIOB, GPIO_Pin_7
#define Pin_INT_PCF8563 GPIOC, GPIO_Pin_13
/* Pins Operation */
#define SCL_PCF8563_Set   GPIO_SetBits(Pin_SCL_PCF8563)
#define SCL_PCF8563_Reset GPIO_ResetBits(Pin_SCL_PCF8563)

#define SDA_PCF8563_Set   GPIO_SetBits(Pin_SDA_PCF8563)
#define SDA_PCF8563_Reset GPIO_ResetBits(Pin_SDA_PCF8563)
#define SDA_PCF8563       GPIO_ReadInputDataBit(Pin_SDA_PCF8563)
/* Operation Status */
#define PCF8563_Write 0
#define PCF8563_Read  1
/* Work Status */
#define PCF8563_Error 1
/* Control and Status Registers */
#define PCF8563_Register_Control_Status_1 0x00
#define PCF8563_Register_Control_Status_2 0x01
/* Time and Date Registers */
#define PCF8563_Register_VL_Seconds       0x02
#define PCF8563_Register_Minutes          0x03
#define PCF8563_Register_Hours            0x04
#define PCF8563_Register_Days             0x05
#define PCF8563_Register_Weekdays         0x06
#define PCF8563_Register_Century_Months   0x07
#define PCF8563_Register_Years            0x08
/* Alarm Registers */
#define PCF8563_Register_Minute_Alarm     0x09
#define PCF8563_Register_Hour_Alarm       0xA0
#define PCF8563_Register_Day_Alarm        0xB0
#define PCF8563_Register_Weekday_Alarm    0x0C
/* CLKOUT Control Register */
#define PCF8563_Register_CLKOUT_Control   0x0D
/* Timer Register */
#define PCF8563_Register_Timer_Control    0x0E
#define PCF8563_Register_Timer            0x0F
/* Public variable prototypes ------------------------------------------------*/
extern char RAM_PCF8563;
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_PCF8563(void);
extern void Start_PCF8563(void);
extern void Stop_PCF8563(void);
extern char Operate_PCF8563(char, char, char);
#endif /* __APP_PCF8563_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
