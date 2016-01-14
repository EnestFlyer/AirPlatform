#include "../../HARDWARE/HCSR04/HCSR04.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SOFTWARE/Sort/Sort.h"

void HCSR04_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   //推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TRIG=0;
}

int HCSR04_GetDistance()
{
	int counter=0;
	TRIG=1;
	delay_us(15);
	TRIG=0;
	while(PAin(1)==0) ;
	while(PAin(1))
	{
		delay_us(20);
		counter++;
	}
	return (int)counter*34/100;
}

float HCSR04_GetDistance_Average(u8 times)
{
	u8 i=0;
	float sum=0;
	for(i=0;i<times;i++)
	{
		sum=sum+HCSR04_GetDistance();
	}
	return sum/times;
}

int HCSR04_GetDistance_Filter()
{
	u8 i=0;
	int sum=0;
	int sample[8];
	for(i=0;i<6;i++)
	{
		sample[i]=HCSR04_GetDistance();
		delay_ms(15);
	}
	
	Bubble_Sort(sample,6);
	for(i=2;i<4;i++)
	{
		sum=sample[i+1]+sum;
	}
	
	return (int)sum/2;
}









