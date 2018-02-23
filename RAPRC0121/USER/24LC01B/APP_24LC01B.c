/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_24LC01B.c
** Descriptions:            Application Chip 24LC01B
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JG
** Created date:            2015-6-16
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
#include "APP_24LC01B.h"
#include "systick.h"
/* Private variable prototypes -----------------------------------------------*/
char RAM_24LC01B;
/* Private function prototypes -----------------------------------------------*/
void Configure_24LC01B(void);
void Initialize_24LC01B(void);
void I2C_Start_24LC01B(void);
void I2C_Stop_24LC01B(void);
char I2C_Acknowledge_24LC01B(void);
void I2C_SD_24LC01B(char);
char I2C_RD_24LC01B(void);
char Write_24LC01B(char, char);
char Read_24LC01B(char);
char Operate_24LC01B(char, char, char);
/*******************************************************************************
* Function Name  : Configure_24LC01B
* Description    : Configure the pins of 24LC01B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_24LC01B(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /*
  Configure the Pins of 24LC01B:
                                SCL -> PB10,
                                SDA -> PB11,
                                WP  -> PB12,
  */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 |
                                  GPIO_Pin_11 |
                                  GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 |
                                  GPIO_Pin_11 |
                                  GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Initialize_24LC01B
* Description    : start 24LC01B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_24LC01B(void)
{
  Configure_24LC01B();
  Systick_Delay_N_millisecond(1);

  WP_24LC01B_Set;
  SCL_24LC01B_Set;
  SDA_24LC01B_Set; //空闲时SDA,SCL同时为高电平
}

/*******************************************************************************
* Function Name  : I2C_Start_24LC01B
* Description    : start I2C of 24LC01B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_Start_24LC01B(void)    //启动SDA由高到低
{
  SDA_24LC01B_Set;                //SDA拉高
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;               //SCL拉高
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Reset;             //SDA在SCL高电平时拉低，起始条件开始(正常数据传输时，只允许SDA在SCL低电平时改变电平)
  Systick_Delay_N_microsecond(5);
}

/*******************************************************************************
* Function Name  : I2C_Stop_24LC01B
* Description    : stop I2C of 24LC01B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_Stop_24LC01B(void)   //停止SDA由低到高
{
  SDA_24LC01B_Reset;            //SDA拉低
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;              //SCL拉高
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Set;              //SDA在SCL高电平时拉高，停止条件开始(正常数据传输时，只允许SDA在SCL低电平时改变电平)
  Systick_Delay_N_microsecond(5);
}

/*******************************************************************************
* Function Name  : I2C_Acknowledge_24LC01B
* Description    : operate with I2C Acknowledge of 24LC01B
* Input          : None
* Output         : None
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char I2C_Acknowledge_24LC01B(void)
{
  unsigned char i;
  char temp_Status;

  SCL_24LC01B_Reset;
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Set;   //SDA拉高，等待ACK信号应答
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;  //SCL拉高，停止数据传送，等待ACK信号应答
  Systick_Delay_N_microsecond(5);
  i = 0;
  while((SDA_24LC01B == 1) && (i < 100))   //在响应时间内等待ACK信号应答，SDA=0应答，SDA=1未应答
  {
    Systick_Delay_N_microsecond(5);
    i++;
  }
  temp_Status = SDA_24LC01B;
  SCL_24LC01B_Reset;
  Systick_Delay_N_microsecond(5);

  return temp_Status;
}

/*******************************************************************************
* Function Name  : I2C_SD_24LC01B
* Description    : send the data with I2C to 24LC01B
* Input          : temp_Data
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_SD_24LC01B(char temp_Data)
{
  unsigned char i;

  SCL_24LC01B_Reset;              //SCL拉低，允许SDA改变电平
  Systick_Delay_N_microsecond(5);
  for (i =0; i< 8; i++)
  {
    if ((temp_Data & 0x80) == 0x80)
    {
      SDA_24LC01B_Set;         //接收到11，SDA拉高
    }
    else
    {
      SDA_24LC01B_Reset;       //接收到0，SDA拉低
    } 
    temp_Data <<= 1;                //temp_Data左移一位
    Systick_Delay_N_microsecond(5);
    SCL_24LC01B_Set;               //SCL拉高，SDA不允许改变电平
    Systick_Delay_N_microsecond(5);
    SCL_24LC01B_Reset;             //SCL拉低，允许SDA改变电平
    Systick_Delay_N_microsecond(5);
  }
}

/*******************************************************************************
* Function Name  : I2C_RD_24LC01B
* Description    : receive the data with I2C from 24LC01B
* Input          : None
* Output         : None
* Return         : temp_Data
* Attention      : None
*******************************************************************************/
char I2C_RD_24LC01B(void)
{
  unsigned char i;
  char temp_Data;

  SCL_24LC01B_Reset;
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Set;
  Systick_Delay_N_microsecond(5);
  for (i = 0; i < 8; i++)
  {
    SCL_24LC01B_Reset;
    Systick_Delay_N_microsecond(5);
    SCL_24LC01B_Set;
    Systick_Delay_N_microsecond(5);
    temp_Data <<= 1;
    if (SDA_24LC01B == 1)
    {
      temp_Data |= 0x01;     //高电平读1
    }
    else
    {
      temp_Data &= (~0x01); //低电平读0
    }
  }
  SCL_24LC01B_Reset;
  Systick_Delay_N_microsecond(5);

  return temp_Data;
}

/*******************************************************************************
* Function Name  : Write_24LC01B
* Description    : write data to 24LC01B
* Input          : temp_Address, temp_Data
* Output         : None
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char Write_24LC01B(char temp_Address, char temp_Data)
{
  char temp_Status;

  temp_Status = 0;
  I2C_Start_24LC01B();
  I2C_SD_24LC01B(0xA0);
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_SD_24LC01B(temp_Address);
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_SD_24LC01B(temp_Data);
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_Stop_24LC01B();
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_Stop_24LC01B();

  return temp_Status;
}

/*******************************************************************************
* Function Name  : Read_24LC01B
* Description    : read data from 24LC01B
* Input          : temp_Address
* Output         : RAM_24LC01B
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char Read_24LC01B(char temp_Address)
{
  char temp_Status;

  temp_Status = 0;
  I2C_Start_24LC01B();
  I2C_SD_24LC01B(0xA0);
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_SD_24LC01B(temp_Address);
  temp_Status = I2C_Acknowledge_24LC01B();
  I2C_Start_24LC01B();
  I2C_SD_24LC01B(0xA1);
  temp_Status = I2C_Acknowledge_24LC01B();
  RAM_24LC01B = I2C_RD_24LC01B();
  I2C_Stop_24LC01B();

  return temp_Status;
}

/*******************************************************************************
* Function Name  : Operate_24LC01B
* Description    : operation 24LC01B, it is reading or writing
* Input          : temp_Status, temp_Address, temp_Data
* Output         : RAM_24LC01B
* Return         : temp_Status
* Attention      : if operate the reading,
                   the data would be saved in the variable-RAM_24LC01B
*******************************************************************************/
char Operate_24LC01B(char temp_Status,
                     char temp_Address,
                     char temp_Data)
{
  WP_24LC01B_Reset;  //WP引脚置零，写操作使能
  Systick_Delay_N_microsecond(5);
  if (temp_Status == 0)
  {
    temp_Status = 0;
    temp_Status = Write_24LC01B(temp_Address, temp_Data);
  }
  else
    if (temp_Status == 1)
    {
      temp_Status = 0;
      temp_Status = Read_24LC01B(temp_Address);
    }
  WP_24LC01B_Set; //WP引脚置1，写操作被禁止，但是读操作不受影响
  Systick_Delay_N_microsecond(5);

  return temp_Status;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
