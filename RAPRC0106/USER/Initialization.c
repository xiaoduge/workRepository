/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Initialization.c
** Descriptions:            system initialization
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-2-10
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
#include "Initialization.h"
/* Public function prototypes ------------------------------------------------*/

void DO_Initialization(void);

/*******************************************************************************
* Function Name  : DO_Initialization
* Description    : Configure the Pins of the GPIO to the AD9834
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void DO_Initialization(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* DO1 -> PC9, DO2 -> PC10 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_SetBits(GPIOC, GPIO_Pin_9);
  GPIO_SetBits(GPIOC, GPIO_Pin_10);
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
