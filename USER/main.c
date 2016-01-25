#include "stm32f10x.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/sys/sys.h"
#include "string.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/HCSR04/HCSR04.h"
#include "../../HARDWARE/OLED/oled.h"

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
	char val2str[]="50";
	char SelfCheck='O';
	
	/////////////////////以上变量定义///////////////////////////
	
	delay_init(72);
	USART1_Init(19200);//与地面站传递命令
	USART2_Init(115200);//与X86板子传递命令
	USART3_Init(115200);//调试用
	HCSR04_Init();
	ResetOLED();
	OLED_Init();
	Key_Init();
	///////////////以上初始化///////////////////////
	OLED_ShowString(35,20,"READY",24);
	OLED_Refresh_Gram();
	delay_ms(1000);
	OLED_Clear();
	
	while(KEY==1)
	{
		OLED_ShowString(0,0,"Self checking now...",12);
		OLED_Refresh_Gram();
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
		}//接受来自X86的命令,用于自检。
		
		if(flag==1)
		{
			SelfCheck=TempOrPressure(temp);
				{
					if(SelfCheck=='C')
					{
						value=ValueOfMea(temp);
						if(value==1)
						{
							OLED_ShowString(0,15,"Environment ok",12);
						}
						if(value==2)
						{
							OLED_ShowString(0,30,"The data chain ok",12);
						}
						if(value==0)
						{
							OLED_ShowString(0,42,"Checking fail...",12);
						}
					}
				}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
		OLED_Refresh_Gram();
	}
	OLED_Clear();
	/////////////////////////以上对上位机的自检，按键强制结束//////////////////
	
	
	OLED_ShowString(0,0,"Parameters",16);
	OLED_ShowString(0,16,"X=",12);
	OLED_ShowString(0,28,"Y=",12);
  OLED_ShowString(0,40,"S=",12);
  OLED_ShowString(0,52,"D=",12);
	OLED_Refresh_Gram();
	flag=0;//复位flag
	///////////显示参数////////////////////////////////

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
				printf1("\"S\":\"%ld\"\r\n",value);
				OLED_ShowNum(20,40,value,6,12);
				counter++;
			}  
			
			if(mode=='X')
			{
				value=ValueOfMea(temp);
				printf1("\"X\":\"%ld\"\r\n",value);
				OLED_ShowNum(20,16,value,6,12);
				counter++;
			}
			else if(mode=='Y')
			{
				value=ValueOfMea(temp);
				printf1("\"Y\":\"%ld\"\r\n",value);
				OLED_ShowNum(20,28,value,6,12);
				counter++;
			}
			if(counter==3)
			{
				delay_ms(100);
				printf1("\"D\":\"%ld\"\r\n",HCSR04_GetDistance_Filter());
				//OLED_ShowNum(20,52,value,6,12);
				counter=0;
			}
			OLED_Refresh_Gram();
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}
}

