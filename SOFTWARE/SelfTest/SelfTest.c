#include "../../SOFTWARE/SelfTest/SelfTest.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/E17_TTL500/E17_TTL500.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/OLED/oled.h"
#include "string.h"

extern u16 USART_RX1_STA;
extern u8 Rx1Buf[Rx1Length];

u8 DataChain_SelfTest()//�����������Լ죬�ɹ�����1
{
	u8 ErrFlag=0;
	u8 len=0;
	u8 temp[100];
	u8 flag=0;
	u8 t=0;
	char command='0';
	
	#ifdef __COMMAND_MODE
		ErrFlag=E17_SelfTest();//ֻ��������ģʽ�²�����e17�Լ�
	#endif
	 
	#ifdef __TRANSPARENT_MODE
		printf1("\"S\":\"%ld\"\r\n",ErrFlag);
	#endif
		//�����͸��ģʽ����Ĭ��E17ģ���������ģ�û�а취�Լ졣
	
	#ifdef __COMMAND_MODE
		E17_SendMsg(CMD_S_PARAM,ErrFlag);
	#endif
	
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
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='S')
			{
				if(ValueOfMea(temp)==7)//�ڶ������ֿ�ʼ
				{
					break;
				}
			}
			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}
	
	#ifdef __TRANSPARENT_MODE
		printf1("\"S\":\"%ld\"\r\n",8);
	#endif

	#ifdef __COMMAND_MODE
		E17_SendMsg(CMD_S_PARAM,8);
	#endif
	//8��ʾ�ڶ������ֽ���	
	delay_ms(100);
	OLED_ShowString(0,30,"The data chain ok",12);
	OLED_Refresh_Gram();
	
	return 1;
}












































































