#include "./../SOFTWARE/Launch/Launch.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/HCSR04/HCSR04.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"

extern u16 USART_RX1_STA;
extern u8 Rx1Buf[Rx1Length];

void AutoLaunch()
{
	u8 len=0;
	u8 temp[100];
	u8 flag=0;
	u8 t=0;
	char command='0';
	
	while(1)
	{
		if(USART_RX1_STA&0x8000)
		{					   
			len=USART_RX1_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=Rx1Buf[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			flag=1;
			USART_RX1_STA=0;
		}
		
		if()
		{
		
		}
	
	}


}
























