/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_DC.c
** Descriptions:            Application Data Conversion
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-2-13
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
#include "APP_CodeConversion.h"

char ASCII_Number[10] =
{
'0',//0
'1',//1
'2',//2
'3',//3
'4',//4
'5',//5
'6',//6
'7',//7
'8',//8
'9',//9
};

char Ram_CCD[4];

void Data_to_ASCII_Code(unsigned int, unsigned char);
/*******************************************************************************
* Function Name  : ASCII_Code_Conversion
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ASCII_Code_Conversion(unsigned int temp_Data, unsigned char temp_Length)
{
  switch (temp_Length)
  {
    case 4:
      temp_Data = temp_Data % 10000;
      Ram_CCD[3] = ASCII_Number[temp_Data / 1000];
    case 3:
      temp_Data = temp_Data % 1000;
      Ram_CCD[2] = ASCII_Number[temp_Data / 100];
    case 2:
      temp_Data = temp_Data % 100;
      Ram_CCD[1] = ASCII_Number[temp_Data / 10];
    case 1:
      temp_Data = temp_Data % 10;
      Ram_CCD[0] = ASCII_Number[temp_Data / 1];
      break;
    default:
      break;
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
