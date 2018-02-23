/****************************************Copyright (c)****************************************************
**                                      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               systick.h
** Descriptions:            None
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

#ifndef __SYSTICK_H
#define __SYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_systick.h"

/* Private function prototypes -----------------------------------------------*/
extern void Systick_Initialization(void);
extern void Systick_Delay_N_microsecond(unsigned short int);
extern void Systick_Delay_N_millisecond(unsigned short int);
extern void Systick_Delay_N_second(unsigned short int);

#endif /* __SYSTICK_H */
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/






























