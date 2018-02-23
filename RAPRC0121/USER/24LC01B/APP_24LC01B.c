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
  SDA_24LC01B_Set; //����ʱSDA,SCLͬʱΪ�ߵ�ƽ
}

/*******************************************************************************
* Function Name  : I2C_Start_24LC01B
* Description    : start I2C of 24LC01B
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_Start_24LC01B(void)    //����SDA�ɸߵ���
{
  SDA_24LC01B_Set;                //SDA����
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;               //SCL����
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Reset;             //SDA��SCL�ߵ�ƽʱ���ͣ���ʼ������ʼ(�������ݴ���ʱ��ֻ����SDA��SCL�͵�ƽʱ�ı��ƽ)
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
void I2C_Stop_24LC01B(void)   //ֹͣSDA�ɵ͵���
{
  SDA_24LC01B_Reset;            //SDA����
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;              //SCL����
  Systick_Delay_N_microsecond(5);
  SDA_24LC01B_Set;              //SDA��SCL�ߵ�ƽʱ���ߣ�ֹͣ������ʼ(�������ݴ���ʱ��ֻ����SDA��SCL�͵�ƽʱ�ı��ƽ)
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
  SDA_24LC01B_Set;   //SDA���ߣ��ȴ�ACK�ź�Ӧ��
  Systick_Delay_N_microsecond(5);
  SCL_24LC01B_Set;  //SCL���ߣ�ֹͣ���ݴ��ͣ��ȴ�ACK�ź�Ӧ��
  Systick_Delay_N_microsecond(5);
  i = 0;
  while((SDA_24LC01B == 1) && (i < 100))   //����Ӧʱ���ڵȴ�ACK�ź�Ӧ��SDA=0Ӧ��SDA=1δӦ��
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

  SCL_24LC01B_Reset;              //SCL���ͣ�����SDA�ı��ƽ
  Systick_Delay_N_microsecond(5);
  for (i =0; i< 8; i++)
  {
    if ((temp_Data & 0x80) == 0x80)
    {
      SDA_24LC01B_Set;         //���յ�11��SDA����
    }
    else
    {
      SDA_24LC01B_Reset;       //���յ�0��SDA����
    } 
    temp_Data <<= 1;                //temp_Data����һλ
    Systick_Delay_N_microsecond(5);
    SCL_24LC01B_Set;               //SCL���ߣ�SDA������ı��ƽ
    Systick_Delay_N_microsecond(5);
    SCL_24LC01B_Reset;             //SCL���ͣ�����SDA�ı��ƽ
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
      temp_Data |= 0x01;     //�ߵ�ƽ��1
    }
    else
    {
      temp_Data &= (~0x01); //�͵�ƽ��0
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
  WP_24LC01B_Reset;  //WP�������㣬д����ʹ��
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
  WP_24LC01B_Set; //WP������1��д��������ֹ�����Ƕ���������Ӱ��
  Systick_Delay_N_microsecond(5);

  return temp_Status;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
