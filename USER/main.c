#include "stm32f10x.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/sys/sys.h"
#include "string.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/HCSR04/HCSR04.h"

extern u16 USART_RX2_STA;

int main(void)
{
	u8 len=0;
	u8 temp[100];
	u8 t=0;
	u8 flag=0;
	char mode='O';
	long value=0;
	u8 counter=0;
	
	delay_init(72);
	USART1_Init(19200);//与地面站传递命令
	USART2_Init(115200);//与X86板子传递命令
	USART3_Init(115200);//调试用
	HCSR04_Init();
//	while(1)
//	{
//		printf1("\"D\":\"%d\"\r\n",HCSR04_GetDistance());
//		delay_ms(50);
//	}
//	
	while(1)
	{
		if(USART_RX2_STA&0x8000)
		{					   
			len=USART_RX2_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=Rx2Buf[t];
				while((USART2->SR&0X40)==0);//等待发送结束
			}
			flag=1;
			USART_RX2_STA=0;
			//printf3("%s\r\n",temp);
		}//接受来自X86的命令
		
		
		if(flag==1)
		{
			mode=TempOrPressure(temp);
			if(mode=='S')
			{
				value=ValueOfMea(temp);
				printf1("\"S\":\"%d\"\r\n",value);
				counter++;
			}  
			
			if(mode=='X')
			{
				value=ValueOfMea(temp);
				printf1("\"X\":\"%d\"\r\n",value);
				counter++;
			} 
			else if(mode=='Y')
			{
				value=ValueOfMea(temp);
				printf1("\"Y\":\"%d\"\r\n",value);
				counter++;
			}
			if(counter==3)
			{
				delay_ms(100);
				printf1("\"D\":\"%d\"\r\n",HCSR04_GetDistance_Filter());
				counter=0;
			}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}
}

