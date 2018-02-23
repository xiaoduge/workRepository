/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_TPIC6B595.c
** Descriptions:            Application TPIC6B595
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
/* Includes ------------------------------------------------------------------*/
#include "APP_LCM12232B.h"
#include "systick.h"
/* Private variable prototypes -----------------------------------------------*/
char Ram_LM12232B[488];
/* Private function prototypes -----------------------------------------------*/
void Initialize_LCM12232B(void);
void LCM12232B_Write_Command_Left(char);
void LCM12232B_Write_Command_Right(char);
void LCM12232B_Write_Data_Left(char);
void LCM12232B_Write_Data_Right(char);
void LCM12232B_Display_Page(void);
void LCM12232B_CLS(void);
void LCM12232B_Loading_Word(unsigned char, unsigned char, unsigned char);
void LCM12232B_Loading_Line(unsigned char, char *);
void LCM12232B_Loading_Page(char *);
/*******************************************************************************
* Function Name  : Initialize_LCM12232B
* Description    : start LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_LCM12232B(void)
{
  GPIO_ResetBits(SN74ALVC164245_2DIR);
  GPIO_SetBits(LCM12232_RST);
  GPIO_SetBits(LCM12232_BL);
  GPIO_ResetBits(LCM12232_V0);
  Systick_Delay_N_millisecond(1);

  LCM12232B_Write_Command_Left(0xE2);
  LCM12232B_Write_Command_Right(0xE2);
  LCM12232B_Write_Command_Left(0xA9);
  LCM12232B_Write_Command_Right(0xA9);
  LCM12232B_Write_Command_Left(0xC0);
  LCM12232B_Write_Command_Right(0xC0);
  LCM12232B_Write_Command_Left(0xA4);
  LCM12232B_Write_Command_Right(0xA4);
}

/*******************************************************************************
* Function Name  : LCM12232B_Write_Command_Left
* Description    : Write the Command to the left LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Write_Command_Left(char temp_Data)
{
  int temp_Status;

  GPIO_ResetBits(LCM12232_RS);
  GPIO_SetBits(LCM12232_RW);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
  Systick_Delay_N_microsecond(1);
  do
  {
    GPIO_SetBits(LCM12232_E2);
    temp_Status = GPIO_ReadInputData(GPIOC) & 0x80;
    GPIO_ResetBits(LCM12232_E2);
  } while (temp_Status == 0x80);

  GPIO_SetBits(SN74ALVC164245_2DIR);
  GPIO_ResetBits(LCM12232_RS);
  GPIO_ResetBits(LCM12232_RW);
  GPIO_SetBits(LCM12232_E1);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | temp_Data);
  Systick_Delay_N_microsecond(1);
  GPIO_ResetBits(LCM12232_E1);
  GPIO_ResetBits(SN74ALVC164245_2DIR);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
}

/*******************************************************************************
* Function Name  : LCM12232B_Write_Command_Right
* Description    : Write the Command to the right LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Write_Command_Right(char temp_Data)
{
  int temp_Status;

  GPIO_ResetBits(LCM12232_RS);
  GPIO_SetBits(LCM12232_RW);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
  Systick_Delay_N_microsecond(1);
  do
  {
    GPIO_SetBits(LCM12232_E1);
    temp_Status = GPIO_ReadInputData(GPIOC) & 0x80;
    GPIO_ResetBits(LCM12232_E1);
  } while (temp_Status == 0x80);

  GPIO_SetBits(SN74ALVC164245_2DIR);
  GPIO_ResetBits(LCM12232_RS);
  GPIO_ResetBits(LCM12232_RW);
  GPIO_SetBits(LCM12232_E2);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | temp_Data);
  Systick_Delay_N_microsecond(1);
  GPIO_ResetBits(LCM12232_E2);
  GPIO_ResetBits(SN74ALVC164245_2DIR);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
}

/*******************************************************************************
* Function Name  : LCM12232B_Write_Data_Left
* Description    : Write the Data to the left LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Write_Data_Left(char temp_Data)
{
  int temp_Status;

  GPIO_ResetBits(LCM12232_RS);
  GPIO_SetBits(LCM12232_RW);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
  Systick_Delay_N_microsecond(1);
  do
  {
    GPIO_SetBits(LCM12232_E2);
    temp_Status = GPIO_ReadInputData(GPIOC) & 0x80;
    GPIO_ResetBits(LCM12232_E2);
  } while (temp_Status == 0x80);

  GPIO_SetBits(SN74ALVC164245_2DIR);
  GPIO_SetBits(LCM12232_RS);
  GPIO_ResetBits(LCM12232_RW);
  GPIO_SetBits(LCM12232_E1);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | temp_Data);
  Systick_Delay_N_microsecond(1);
  GPIO_ResetBits(LCM12232_E1);
  GPIO_ResetBits(SN74ALVC164245_2DIR);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
}

/*******************************************************************************
* Function Name  : LCM12232B_Write_Data_Right
* Description    : Write the Data to the right LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Write_Data_Right(char temp_Data)
{
  int temp_Status;

  GPIO_ResetBits(LCM12232_RS);
  GPIO_SetBits(LCM12232_RW);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
  Systick_Delay_N_microsecond(1);
  do
  {
    GPIO_SetBits(LCM12232_E1);
    temp_Status = GPIO_ReadInputData(GPIOC) & 0x80;
    GPIO_ResetBits(LCM12232_E1);
  } while (temp_Status == 0x80);

  GPIO_SetBits(SN74ALVC164245_2DIR);
  GPIO_SetBits(LCM12232_RS);
  GPIO_ResetBits(LCM12232_RW);
  GPIO_SetBits(LCM12232_E2);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | temp_Data);
  Systick_Delay_N_microsecond(1);
  GPIO_ResetBits(LCM12232_E2);
  GPIO_ResetBits(SN74ALVC164245_2DIR);
  GPIO_Write(GPIOC, (GPIO_ReadOutputData(GPIOC) & 0xFF00) | 0xFF);
}

/*******************************************************************************
* Function Name  : LCM12232B_Display_Page
* Description    : Display the page of LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Display_Page(void)
{
  unsigned char i, j;
  char *ptr;

  ptr = Ram_LM12232B;

  for (i = 0; i < 4; i++)
  {
    LCM12232B_Write_Command_Left(0xB8 | i);
    LCM12232B_Write_Command_Left(0x00);
    for (j = 0; j < 61; j++)
    {
      LCM12232B_Write_Data_Left(*ptr++);
    }
    LCM12232B_Write_Command_Right(0xB8 | i);
    LCM12232B_Write_Command_Right(0x00);
    for(j = 61; j < 122; j++)
    {
      LCM12232B_Write_Data_Right(*ptr++);
    }
  }

//  LCM12232B_Write_Command_Left(0xAE);
//  LCM12232B_Write_Command_Right(0xAE);

  LCM12232B_Write_Command_Left(0xAF);
  LCM12232B_Write_Command_Right(0xAF);
}

/*******************************************************************************
* Function Name  : LCM12232B_CLS
* Description    : Clean the RAM of LCM12232B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_CLS(void)
{
  unsigned int i;

  for (i = 0; i < 488; i++)
  {
    Ram_LM12232B[i] = 0x00;
  }
}

/*******************************************************************************
* Function Name  : LCM12232B_Loading_Word
* Description    : loading the word to LCM12232B
* Input          : temp_Line, temp_Column
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Loading_Word(unsigned char temp_No,
                            unsigned char temp_Line,
                            unsigned char temp_Column)
{
  unsigned int i, j;

  switch (temp_No)
  {
    case 0:
      for (i = 0; i < 2; i++)
      {
        for (j = 0; j < 6; j++)
        {
          Ram_LM12232B[(((temp_Line * 2 - 1) - 1 + i) * 122) + (temp_Column - 1) + j] |= Ram_6X12_GT21L16S2W[(j * 2) + i];
        }
      }
      break;
    case 1:
      for (i = 0; i < 2; i++)
      {
        for (j = 0; j < 11; j++)
        {
          Ram_LM12232B[(((temp_Line * 2 - 1) - 1 + i) * 122) + (temp_Column - 1) + j] |= Ram_11X12_GT21L16S2W[(j * 2) + i];
        }
      }
      break;
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : LCM12232B_Loading_Line
* Description    : loading the line to LCM12232B
* Input          : temp_Line
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Loading_Line(unsigned char temp_Line, char *ptr)
{
  unsigned char i, j;

  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 121; j++)
    {
      Ram_LM12232B[(((temp_Line * 2 - 1) - 1 + i) * 122) + j] = *ptr++;
    }
  }
}

/*******************************************************************************
* Function Name  : LCM12232B_Loading_Page
* Description    : loading the page to LCM12232B
* Input          : temp_Line
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCM12232B_Loading_Page(char *ptr)
{
  unsigned char i, j;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 122; j++)
    {
      Ram_LM12232B[(i * 122) + j] = *ptr++;
    }
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
