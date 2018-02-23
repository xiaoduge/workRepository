/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Key.c
** Descriptions:            Application Key
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
/* Includes ------------------------------------------------------------------*/
#include "APP_Key.h"
#include "systick.h"
/* Private function prototypes -----------------------------------------------*/
void Configure_Key(void);
void Initialize_Key(void);
char Read_Key(void);
/*******************************************************************************
* Function Name  : Configure_Key
* Description    : configure the pins of GPIO to the Key
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_Key(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* Key1 -> PA8, Key2 -> PA9, Key3 -> PA10, Key4 -> PA11 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_Key
* Description    : start key operation
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_Key(void)
{
  Configure_Key();
  Systick_Delay_N_millisecond(1);
}

/*******************************************************************************
* Function Name  : Read_Key
* Description    : Read the Key Value from the GPIO
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
char Read_Key(void)
{
  char temp_Data;

  temp_Data = (~(GPIO_ReadInputData(GPIOA) >> 8)) & 0x0F;
  Systick_Delay_N_millisecond(50);

  if (temp_Data != 0)
  {
    if (temp_Data == ((~(GPIO_ReadInputData(GPIOA) >> 8)) & 0x0F))
    {
      while (((~(GPIO_ReadInputData(GPIOA) >> 8)) & 0x0F) != 0);
      Systick_Delay_N_millisecond(10);
      return temp_Data;
    }
  }

  return 0x00;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
