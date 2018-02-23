/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Key.h
** Descriptions:            Key.c header File
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-6-29
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
#ifndef __APP_Key_H
#define __APP_Key_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
#define Key_NC    0x00
#define Key_Up    0x01
#define Key_Down  0x08
#define Key_Left  0x02
#define Key_Right 0x04
#define Key_UV_Test (Key_Up | Key_Left)
#define Key_Reset (Key_Down | Key_Right)
/* Public variable prototypes ------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
extern void Initialize_Key(void);
extern char Read_Key(void);
#endif /* __APP_Key_H */

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/