/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               systick.c
** Descriptions:            
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

/* Includes ------------------------------------------------------------------*/
#include "systick.h"

/* Private variables ---------------------------------------------------------*/
static unsigned short int a_microsecond;

void Systick_Initialization(void);
void Systick_Delay_N_microsecond(unsigned short int);
void Systick_Delay_N_millisecond(unsigned short int);
void Systick_Delay_N_second(unsigned short int);
/*******************************************************************************
* Function Name  : Systick_Initialization
* Description    : Initialization Systick
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Systick_Initialization(void)
{
  RCC_ClocksTypeDef RCC_ClocksStatus;

  RCC_GetClocksFreq(&RCC_ClocksStatus);

  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

  a_microsecond = RCC_ClocksStatus.HCLK_Frequency / 1000000;
}

/*******************************************************************************
* Function Name  : Systick_Delay_N_microsecond
* Description    : None
* Input          : N microsecond
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Systick_Delay_N_microsecond(unsigned short int temp_N_microsecond)
{
  SysTick_SetReload(a_microsecond * temp_N_microsecond);

  SysTick_CounterCmd(SysTick_Counter_Clear);

  SysTick_CounterCmd(SysTick_Counter_Enable);
  do
  {}while (SysTick_GetFlagStatus(SysTick_FLAG_COUNT) == RESET);
  SysTick_CounterCmd(SysTick_Counter_Disable);
}

/*******************************************************************************
* Function Name  : Systick_Delay_N_millisecond
* Description    : None
* Input          : N millisecond
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Systick_Delay_N_millisecond(unsigned short int temp_N_millisecond)
{
  while (temp_N_millisecond--)
  {
    Systick_Delay_N_microsecond(999);
  }
}

/*******************************************************************************
* Function Name  : Systick_Delay_N_second
* Description    : None
* Input          : N second
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Systick_Delay_N_second(unsigned short int temp_N_second)
{
  while (temp_N_second--)
  {
    Systick_Delay_N_millisecond(1000);
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
















