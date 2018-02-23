/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_TSM.h
** Descriptions:            APP_TSM.c header File
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
#ifndef __APP_TSM_H
#define __APP_TSM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Define --------------------------------------------------------------------*/
#define LogoNo_RephiLe 0

#define LanguageNo_Min 1
#define LanguageNo_Max 2
#define LanguageNo_English            1
#define LanguageNo_Simplified_Chinese 2

#define Off 0
#define On  1

#define Value_Hour_Max 23
#define Value_Hour_Min 0

#define Value_Minute_Max 59
#define Value_Minute_Min 0

#define Value_Second_Max 59
#define Value_Second_Min 0

#define Value_Year_Max 99
#define Value_Year_Min 0

#define Value_Month_Max 12
#define Value_Month_Min 1

#define Value_Day_Max 31
#define Value_Day_Min 1

#define UV_Loop_Time_Max 60
#define UV_Loop_Time_Min 0

#define UV_Used_Time_Max 9999
#define UV_Used_Time_Min 0

#define UV_Life_Max 999
#define UV_Life_Min 0

#define Page_2No_Max 4
#define Page_2No_Min 1

#define _6X12_  1
#define _11X12_ 2

#define Test_Time 10
/* Save Address */
#define Address_Language         0x00
#define Address_UV_Loop_Time     0x01
#define Address_UV_Life_MSB      0x02
#define Address_UV_Life_LSB      0x03
#define Address_UV_Used_Time_MSB 0x04
#define Address_UV_Used_Time_LSB 0x05
/* Public variable prototypes ------------------------------------------------*/
extern unsigned char Start_Flag;
extern unsigned char UVStatusNo;
extern signed int UV_Used_Time;
extern signed int UV_Remainder_Time;
extern signed char UV_Loop_Time;
extern signed char Value_Hour;
extern signed char Value_Minute;
extern signed char Value_Second;
extern signed char Value_Year;
extern signed char Value_Month;
extern signed char Value_Day;
extern unsigned char Save_UVUT_Flag;
extern unsigned char PageNo;
extern signed int UV_Residual_Life;
/* Public function prototypes ------------------------------------------------*/
extern void Initialize_TSM(void);
extern void Display_Logo(void);
extern void Display_Product_Title(void);
extern void Display_PSN_and_Vision(void);
extern void Page_Manage(void);
extern void Page_1(void);
extern void Page_2(void);
extern void Page_2_1(void);
extern void Page_2_2(void);
extern void Page_2_3(void);
extern void Page_2_4(void);
extern void Loading_Page_1(void);
extern void Refresh_Page(void);
#endif /* __APP_TSM_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
