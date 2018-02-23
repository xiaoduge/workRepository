/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               APP_PCF8563.c
** Descriptions:            Application Chip PCF8563
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
#include "APP_PCF8563.h"
#include "systick.h"
/* Private variable prototypes -----------------------------------------------*/
char RAM_PCF8563;
/* Private function prototypes -----------------------------------------------*/
void Configure_PCF8563(void);
void Initialize_PCF8563(void);
void I2C_Start_PCF8563(void);
void I2C_Stop_PCF8563(void);
char I2C_Acknowledge_PCF8563(void);
void I2C_SD_PCF8563(char);
char I2C_RD_PCF8563(void);
char Write_PCF8563(char, char);
char Read_PCF8563(char);
void Start_PCF8563(void);
void Stop_PCF8563(void);
char Operate_PCF8563(char, char, char);
/*******************************************************************************
* Function Name  : Configure_PCF8563
* Description    : configure the pins of PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Configure_PCF8563(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  /* Configure the Pins of PCF8563: SCL -> PB6, SDA -> PB7, INT -> PC13*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  //设置优先级分组，先占优先级0位，从优先级4位
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断线15-10中断，设定中断源为EXIT13
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//中断占优先级为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     //副优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能中断
  NVIC_Init(&NVIC_InitStructure);

  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //设置EXTI线路为中断请求(EXTI_Mode_Event为EXTI线路为事件中断)
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//设置输入线路下降沿为中断请求
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;           //选择待使能或失能的外部线路
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;         //定义选中线路的状态
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);  //选择GPIO管脚作为外部中断线路
  EXTI_ClearITPendingBit(EXTI_Line13);               //清除EXTI线路挂起位
}

/*******************************************************************************
* Function Name  : Initialize_PCF8563
* Description    : start PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Initialize_PCF8563(void)
{
  Configure_PCF8563();
  Systick_Delay_N_millisecond(1);

  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Timer, 0x01);
  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Timer_Control, 0x82);  //定时器有效，定时器时钟频率=1Hz
  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Control_Status_1, 0x00);//普通模式，芯片时钟运行，电源复位功能失效
  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Control_Status_2, 0x11); //INT脉冲有效，定时器中断有效
}

/*******************************************************************************
* Function Name  : I2C_Start_PCF8563
* Description    : start I2C of PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_Start_PCF8563(void)
{
  SCL_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  SDA_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  SDA_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);
}

/*******************************************************************************
* Function Name  : I2C_Stop_PCF8563
* Description    : stop I2C of PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_Stop_PCF8563(void)
{
  SDA_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);
  SCL_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  SDA_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
}

/*******************************************************************************
* Function Name  : I2C_Acknowledge_PCF8563
* Description    : operate with I2C acknowleage of PCF8563
* Input          : None
* Output         : None
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char I2C_Acknowledge_PCF8563(void)
{
  unsigned char i;
  char temp_Status;

  SCL_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);
  SDA_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  SCL_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  i = 0;
  while((SDA_PCF8563 == 1) && (i < 100))
  {
    Systick_Delay_N_microsecond(10);
    i++;
  }
  temp_Status = SDA_PCF8563;
  SCL_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);

  return temp_Status;
}

/*******************************************************************************
* Function Name  : I2C_SD_PCF8563
* Description    : send the data with I2C to PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void I2C_SD_PCF8563(char temp_Data)
{
  unsigned char i;

  SCL_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);
  for (i =0; i< 8; i++)
  {
    if ((temp_Data & 0x80) == 0x80)
    {
      SDA_PCF8563_Set;
    }
    else
    {
      SDA_PCF8563_Reset;
    }
    Systick_Delay_N_microsecond(10);
    SCL_PCF8563_Set;
    Systick_Delay_N_microsecond(10);
    SCL_PCF8563_Reset;
    temp_Data <<= 1;
  }
  Systick_Delay_N_microsecond(5);
}

/*******************************************************************************
* Function Name  : I2C_RD_PCF8563
* Description    : receive the data with I2C from PCF8563
* Input          : None
* Output         : None
* Return         : temp_Data
* Attention      : None
*******************************************************************************/
char I2C_RD_PCF8563(void)
{
  unsigned char i;
  char temp_Data;

  SCL_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);
  SDA_PCF8563_Set;
  Systick_Delay_N_microsecond(5);
  for (i = 0; i < 8; i++)
  {
    SCL_PCF8563_Reset;
    Systick_Delay_N_microsecond(10);
    SCL_PCF8563_Set;
    Systick_Delay_N_microsecond(10);
    temp_Data <<= 1;
    if (SDA_PCF8563 == 1)
    {
      temp_Data |= 0x01;
    }
    else
    {
      temp_Data &= (~0x01);
    }
  }
  SCL_PCF8563_Reset;
  Systick_Delay_N_microsecond(5);

  return temp_Data;
}

/*******************************************************************************
* Function Name  : Write_PCF8563
* Description    : write data to PCF8563
* Input          : temp_Address, temp_Data
* Output         : None
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char Write_PCF8563(char temp_Address, char temp_Data)
{
  char temp_Status;

  I2C_Start_PCF8563();
  temp_Status = 0;
  I2C_SD_PCF8563(0xA2);//Slave Address - PCF8563 Write
  temp_Status = I2C_Acknowledge_PCF8563();
  I2C_SD_PCF8563(temp_Address);
  temp_Status = I2C_Acknowledge_PCF8563();
  I2C_SD_PCF8563(temp_Data);
  temp_Status = I2C_Acknowledge_PCF8563();
  I2C_Stop_PCF8563();

  return temp_Status;
}

/*******************************************************************************
* Function Name  : Read_PCF8563
* Description    : read data from PCF8563
* Input          : temp_Address
* Output         : RAM_PCF8563
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char Read_PCF8563(char temp_Address)
{
  char temp_Status;

  I2C_Start_PCF8563();
  temp_Status = 0;
  I2C_SD_PCF8563(0xA2);
  temp_Status = I2C_Acknowledge_PCF8563();
  I2C_SD_PCF8563(temp_Address);
  temp_Status = I2C_Acknowledge_PCF8563();
  I2C_Start_PCF8563();
  I2C_SD_PCF8563(0xA3);
  temp_Status = I2C_Acknowledge_PCF8563();
  RAM_PCF8563 = I2C_RD_PCF8563();
  I2C_Stop_PCF8563();

  return temp_Status;
}

/*******************************************************************************
* Function Name  : Start_PCF8563
* Description    : operation status, start PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Start_PCF8563(void)
{
  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Control_Status_1, 0 << 5);
}

/*******************************************************************************
* Function Name  : Stop_PCF8563
* Description    : operation status, stop PCF8563
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void Stop_PCF8563(void)
{
  Operate_PCF8563(PCF8563_Write, PCF8563_Register_Control_Status_1, 1 << 5);
}

/*******************************************************************************
* Function Name  : Operate_PCF8563
* Description    : operation PCF8563 includes writing or reading
* Input          : temp_Status, temp_Address, char temp_Data
* Output         : RAM_PCF8563
* Return         : temp_Status
* Attention      : None
*******************************************************************************/
char Operate_PCF8563(char temp_Status, char temp_Address, char temp_Data)
{
  if (temp_Status == 0)//Write
  {
    temp_Status = 0;
    temp_Status = Write_PCF8563(temp_Address, temp_Data);
  }
  else
    if (temp_Status == 1)//Read
    {
      temp_Status = 0;
      temp_Status = Read_PCF8563(temp_Address);
    }

  return temp_Status;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
