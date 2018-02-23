/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               LED.c
** Descriptions:            Application Key
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
/* Includes ------------------------------------------------------------------*/
#include "APP_LED.h"
#include "systick.h"
/* Private variable prototypes -----------------------------------------------*/
unsigned char LED_Status_No;
/* Private function prototypes -----------------------------------------------*/
void Configure_LED(void);
void Initialize_LED(void);
/*******************************************************************************
* Function Name  : Configure_LED
* Description    : configure the pins of GPIO to the LED
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* LED1 -> PA0, LED2 -> PA1, LED3 -> PA2, LED4 -> PA3 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_LED
* Description    : start LED operation
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_LED(void)
{
  Configure_LED();
  Systick_Delay_N_millisecond(1);

  LED1_G_Off;
  LED1_R_Off;
  LED2_G_Off;
  LED2_R_Off;
}

/*******************************************************************************
* Function Name  : Operate_LED
* Description    : LED operation
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Operate_LED(unsigned char temp_No)
{
  switch (temp_No)
  {
    case 1:
      break;
    case 2:
      break;
    default:
      break;
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
