/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_DI.c
** Descriptions:            Application DI
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-9-1
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
#include "APP_DI.h"
#include "systick.h"
/* Private data prototypes ---------------------------------------------------*/

/* Private variable prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Configure_DI(void);
void Initialize_DI(void);
/*******************************************************************************
* Function Name  : Configure_DI
* Description    : configure the pins of GPIO to the DI
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_DI(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* DI1 -> PC11, DI2 -> PC12 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //…œ¿≠ ‰»Î
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_DI
* Description    : Initialize DI
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_DI(void)
{
  Configure_DI();
  Systick_Delay_N_millisecond(1);

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
