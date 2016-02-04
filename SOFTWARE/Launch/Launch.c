#include "./../SOFTWARE/Launch/Launch.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/HCSR04/HCSR04.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "string.h"
#include "../../HARDWARE/E17_TTL500/E17_TTL500.h"

extern u16 USART_RX1_STA;
extern u8 Rx1Buf[Rx1Length];

extern u16 USART_RX2_STA;
extern u8 Rx2Buf[Rx2Length];

void AutoLaunch()
{
	u8 len=0;
	u8 temp[100];
	u8 flag=0;
	u8 t=0;
	char command='0';
	u8 flagOfX86=0;
	u8 tempOfX86[100];
	u8 lenOfX86=0;
	u8 tOfX86=0;
	
	while(1)
	{
		if(USART_RX1_STA&0x8000)
		{					   
			len=USART_RX1_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
				temp[t]=Rx1Buf[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			flag=1;
			USART_RX1_STA=0;
		}
		
		if(USART_RX2_STA&0x8000)
		{					   
			lenOfX86=USART_RX2_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(tOfX86=0;tOfX86<lenOfX86;tOfX86++)
			{
				tempOfX86[tOfX86]=Rx2Buf[tOfX86];
				while((USART2->SR&0X40)==0);//�ȴ����ͽ���
			}
			flagOfX86=1;
			USART_RX2_STA=0;
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='S')
			{
				if(ValueOfMea(temp)==9)//��G����300cmʱ����������ˡ�
				{
					break;
				}
			}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
		
		#ifdef __TRANSPARENT_MODE
			printf1("\"G\":\"%ld\"\r\n",GROUND_GetDistance_Filter());
		#endif
		
		#ifdef __COMMAND_MODE
			E17_SendMsg(CMD_G_PARAM,GROUND_GetDistance_Filter());
		#endif
		//����߶�
		

	}
}
























