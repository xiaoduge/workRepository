/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_DO.c
** Descriptions:            Application DO
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-7-10
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
#include "APP_DO.h"
#include "systick.h"
/* Private data prototypes ---------------------------------------------------*/

/* Private variable prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Configure_DO(void);
void Initialize_DO(void);
/*******************************************************************************
* Function Name  : Configure_DO
* Description    : configure the pins of GPIO to the DO
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_DO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* DO1 -> PC9, DO2 -> PC10 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_DO
* Description    : Initialize DO
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_DO(void)
{
  Configure_DO();
  Systick_Delay_N_millisecond(1);

  DO1_Reset;
  DO2_Reset;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
