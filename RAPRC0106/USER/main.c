/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            Resistivity Measurement
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

/* Includes ------------------------------------------------------------------*/
#include "APP_TSM.h" 
#include "Initialization.h"
#include "APP_LCM12232B.h"
#include "APP_SN74ALVC164245.h"
#include "APP_GT21L16S2W.h"
#include "APP_PCF8563.h"
#include "APP_24LC01B.h"
#include "APP_Key.h"
#include "APP_DO.h"
#include "APP_DI.h"
#include "APP_LED.h"
#include "systick.h"

/* Define --------------------------------------------------------------------*/
#define Buzzer SN74ALVC164245_1A8

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* Private variable prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void System_Start(void);

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
int main(void)
{
  Systick_Initialization();
  Initialize_GT21L16S2W();
  Initialize_PCF8563();
  Initialize_24LC01B();
  Initialize_LED();
  Initialize_Key();
  Initialize_DO();
  Initialize_DI();
  Initialize_SN74ALVC164245();
  Initialize_LCM12232B();

  System_Start();

  /* Infinite loop */
  while (1)
  {
    Page_1();
    Page_2();
    Page_2_1();
    Page_2_2();
    Page_2_3();
    Page_2_4();
    Refresh_Page();
  }
}

/*******************************************************************************
* Function Name  : System_Start
* Description    : Start System
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void System_Start(void)
{
  Initialize_TSM();
  Systick_Delay_N_second(1);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

