/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_GT21L16S2W.c
** Descriptions:            Application GT21L16S2W(Only Simplified Chinese)
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-6-23
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
#include "APP_GT21L16S2W.h"
#include "systick.h"
/* Private variable prototypes -----------------------------------------------*/
char Ram_6X12_GT21L16S2W[12];
char Ram_11X12_GT21L16S2W[22];
/* Private function prototypes -----------------------------------------------*/
void Configure_GT21L16S2W(void);
void Initialize_GT21L16S2W(void);
void SD_GT21L16S2W(char);
char RD_GT21L16S2W(void);
void Read_GB2312_6X12_GT21L16S2W(int);
void Read_GB2312_11X12_GT21L16S2W(int);
/*******************************************************************************
* Function Name  : Configure_GT21L16S2W
* Description    : configure pins to GT21L16S2W
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_GT21L16S2W(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /*
  Configure the Pins of GT21L16S2W: NSS  -> PA4,  //GT21L16S2W第一个引脚片选输入
                                    SCK  -> PA5,  //GT21L16S2W第6个引脚串行时钟输入
                                    MISO -> PA6, //GT21L16S2W第2个引脚串行数据输出
                                    MOSI -> PA7, //GT21L16S2W第5个引脚串行数据输入
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_GT21L16S2W
* Description    : start GT21L16S2W
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_GT21L16S2W(void)
{
  Configure_GT21L16S2W();
  Systick_Delay_N_millisecond(1);

  SPI_NSS_GT21L16S2W_Set;
  SPI_SCK_GT21L16S2W_Set;
}

/*******************************************************************************
* Function Name  : SD_GT21L16S2W
* Description    : send data to GT21L16S2W
* Input          : temp_Data
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void SD_GT21L16S2W(char temp_Data)
{
  unsigned char i;

  for (i = 0; i < 8; i++)
  {
    SPI_SCK_GT21L16S2W_Reset;

    if ((temp_Data & 0x80) == 0x80)
    {
      SPI_MOSI_GT21L16S2W_Set;
    }
    else
    {
      SPI_MOSI_GT21L16S2W_Reset;
    }
    temp_Data = temp_Data << 1;

    SPI_SCK_GT21L16S2W_Set;
  }
}

/*******************************************************************************
* Function Name  : RD_GT21L16S2W
* Description    : receive data from GT21L16S2W
* Input          : None
* Output         : None
* Return         : temp_Data
* Attention      : None
*******************************************************************************/
char RD_GT21L16S2W(void)
{
  unsigned char i;
  char temp_Data;

  for (i = 0; i < 8; i++)
  {
    SPI_SCK_GT21L16S2W_Reset;

    temp_Data = temp_Data << 1;
    if (SPI_MISO_GT21L16S2W == 1)
    {
      temp_Data |= 1;
    }
    else
    {
      temp_Data &= (~1);
    }

    SPI_SCK_GT21L16S2W_Set;
  }
  return temp_Data;
}

/*******************************************************************************
* Function Name  : Read_GB2312_6X12_GT21L16S2W
* Description    : read the data with width 6 and height 12 from GT21L16S2W
* Input          : temp_Data
* Output         : Ram_6X12_GT21L16S2W
* Return         : None
* Attention      : None
*******************************************************************************/
void Read_GB2312_6X12_GT21L16S2W(int temp_Data)
{
  unsigned char i, j;
  char temp_DataPack[12];
  unsigned char ASCIICode;
  unsigned int FontCode;
  long int BaseAddress, Address;

  ASCIICode = (unsigned char)temp_Data;

  BaseAddress = 0x66D40;

  if ((ASCIICode >= 0x20) && (ASCIICode <= 0x7E))
  {
    Address = (ASCIICode - 0x20) * 12 + BaseAddress;
  }

  BaseAddress=0x66D4C;

  if ((FontCode >= 0xAAA1) && (FontCode <= 0xAAFE))
  {
    Address = (FontCode - 0xAAA1) * 12 + BaseAddress;
  }
  else
    if((FontCode >= 0xABA1) && (FontCode <= 0xABC0))
    {
      Address = (FontCode - 0xABA1 + 95) * 12 + BaseAddress;
    }

  SPI_NSS_GT21L16S2W_Reset;
  SD_GT21L16S2W(0x0B);
  SD_GT21L16S2W((char)(Address >> 16));
  SD_GT21L16S2W((char)(Address >> 8));
  SD_GT21L16S2W((char)(Address >> 0));
  SD_GT21L16S2W(0x00);
  for (i = 0; i < 12; i++)
  {
    temp_DataPack[i] = RD_GT21L16S2W();
  }
  SPI_NSS_GT21L16S2W_Set;

  for (j = 0; j < 6; j++)
  {
    for (i = 0; i < 12; i++)
    {
      if ((temp_DataPack[i] & 0x80) == 0x80)
      {
        if ((i + 2) < 8)
        {
          Ram_6X12_GT21L16S2W[j * 2] |= (1 << (i + 2));
        }
        else
        {
          Ram_6X12_GT21L16S2W[(j * 2) + 1] |= (1 << (i + 2 - 8));
        }
      }
      else
      {
        if ((i + 2) < 8)
        {
          Ram_6X12_GT21L16S2W[j * 2] &= (~(1 << (i + 2)));
        }
        else
        {
          Ram_6X12_GT21L16S2W[(j * 2) + 1] &= (~(1 << (i + 2 - 8)));
        }
      }
      temp_DataPack[i] = temp_DataPack[i] << 1;
    }
  }
}

/*******************************************************************************
* Function Name  : Read_GB2312_11X12_GT21L16S2W
* Description    : read the data with width 11 and height 12 from GT21L16S2W
* Input          : temp_Data
* Output         : Ram_11X12_GT21L16S2W
* Return         : None
* Attention      : None
*******************************************************************************/
void Read_GB2312_11X12_GT21L16S2W(int temp_Data)
{
  unsigned char i, j;
  int temp_DataPack[12];
  unsigned char MSB, LSB;
  long int BaseAddress, Address;

  MSB = (unsigned char)(temp_Data >> 8);
  LSB = (unsigned char)temp_Data;

  BaseAddress=0x3CF80;

  if((MSB >= 0xA1) && (MSB <= 0xA3) && (LSB >= 0xA1))
  {
    Address =((MSB - 0xA1) * 94 + (LSB - 0xA1)) * 24 + BaseAddress;
  }
  else
    if((MSB == 0XA9) && (LSB >= 0xA1))
    {
      Address =(282 + (LSB - 0xA1)) * 24 + BaseAddress;
    }
    else
      if((MSB >= 0xB0) && (MSB <= 0xF7) && (LSB >= 0xA1))
      {
        Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1) + 376) * 24+ BaseAddress;
      }

  SPI_NSS_GT21L16S2W_Reset;
  SD_GT21L16S2W(0x0B);
  SD_GT21L16S2W((char)(Address >> 16));
  SD_GT21L16S2W((char)(Address >> 8));
  SD_GT21L16S2W((char)(Address >> 0));
  SD_GT21L16S2W(0x00);
  for (i = 0; i < 12; i++)
  {
    temp_DataPack[i] = (RD_GT21L16S2W() << 8);
    temp_DataPack[i] |= RD_GT21L16S2W();
  }
  SPI_NSS_GT21L16S2W_Set;

  for (j = 0; j < 11; j++)
  {
    for (i = 0; i < 12; i++)
    {
      if ((temp_DataPack[i] & 0x8000) == 0x8000)
      {
        if ((i + 2) < 8)
        {
          Ram_11X12_GT21L16S2W[j * 2] |= (1 << (i + 2));
        }
        else
        {
          Ram_11X12_GT21L16S2W[(j * 2) + 1] |= (1 << (i + 2 - 8));
        }
      }
      else
      {
        if ((i + 2) < 8)
        {
          Ram_11X12_GT21L16S2W[j * 2] &= (~(1 << (i + 2)));
        }
        else
        {
          Ram_11X12_GT21L16S2W[(j * 2) + 1] &= (~(1 << (i + 2 - 8)));
        }
      }
      temp_DataPack[i] = (temp_DataPack[i] << 1);
    }
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
