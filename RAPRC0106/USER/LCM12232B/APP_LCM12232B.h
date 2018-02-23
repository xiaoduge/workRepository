/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_TPIC6B595.h
** Descriptions:            APP_TPIC6B595.c header File
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
#ifndef __APP_LCM12232B_H
#define __APP_LCM12232B_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "APP_SN74ALVC164245.h"
#include "APP_GT21L16S2W.h"
/* Define --------------------------------------------------------------------*/
/* Pins Definition */
#define LCM12232_RST SN74ALVC164245_1A1
#define LCM12232_E1  SN74ALVC164245_1A2
#define LCM12232_E2  SN74ALVC164245_1A3
#define LCM12232_RW  SN74ALVC164245_1A4
#define LCM12232_RS  SN74ALVC164245_1A5
#define LCM12232_BL  SN74ALVC164245_1A6
#define LCM12232_V0  SN74ALVC164245_1A7

#define LCM12232_DB0 SN74ALVC164245_2A1
#define LCM12232_DB1 SN74ALVC164245_2A2
#define LCM12232_DB2 SN74ALVC164245_2A3
#define LCM12232_DB3 SN74ALVC164245_2A4
#define LCM12232_DB4 SN74ALVC164245_2A5
#define LCM12232_DB5 SN74ALVC164245_2A6
#define LCM12232_DB6 SN74ALVC164245_2A7
#define LCM12232_DB7 SN74ALVC164245_2A8
/* Public variable prototypes ------------------------------------------------*/
extern char Ram_LM12232B[488];
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_LCM12232B(void);
extern void LCM12232B_Display_Page(void);
extern void LCM12232B_CLS(void);
extern void LCM12232B_Loading_Word(unsigned char, unsigned char, unsigned char);
extern void LCM12232B_Loading_Line(unsigned char, char *);
extern void LCM12232B_Loading_Page(char *);
#endif /* __APP_LCM12232B_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
