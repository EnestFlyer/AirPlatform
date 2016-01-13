#include "../../SYSTEM/USART/USART.h"
#include "../../SYSTEM/delay/delay.h"
#include "stm32f10x_exti.h"
#include "../../SOFTWARE/EXTI/exti.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"


#ifdef __TEST_MODE_


void TEST_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PC1用于拉高，PC2用于拉低
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PC3 LED,自动控制时灭，手动控制时亮
}

//外部中断初始化函数
void EXTIX_Init(void)
{
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	/****************************PC0******************************/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI0_IRQHandler(void)
{
	delay_ms(100);
	if(PCin(0)==1)
	{
		HIGH_PIN=1;
		LOW_PIN=0;
		LED=1;//LED灭
	}//手动控制
	else if(PCin(0)==0)
	{
		HIGH_PIN=0;
		LOW_PIN=1;
		LED=0;//LED亮
	}//自动控制
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}


#endif
