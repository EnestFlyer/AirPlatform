#include "../../HARDWARE/E17_TTL500/E17_TTL500.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "string.h"
#include "stdlib.h"
//�ɻ��ˣ����Ǳ����ĵ�ַΪ0x2345
//����վ�ĵ�ַΪ0x5678

#ifdef __COMMAND_MODE

extern u16 USART_RX1_STA;

u8 ResponseDet(char *str)
{
	if(strcmp(str,"OK\r\n")==0)//��ͬ
		return 1;
	else if(strcmp(str,"ERROR\r\n")==0)
		return 2;
	else 
		return 0;
}

u8 E17_SelfTest()//����·�Լ���
{
	int i=0;
	int len=0;
	char temp[100];
	u8 t=0;
	u8 flag=0;
	u8 ErrType=0;//0Ϊ�޴���1Ϊ��ʱ��δ���ܵ�OK,2Ϊ���ܵ�ERROR
	
	printf1("%x%x%x",0xC2,0xC2,0xC2);//��������ɹ�����OK\r\n,׼������ok
	for(i=0;i<1000;i++)
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
		}//����E17ģ��ķ���
		
		if(flag==1)
		{
			if(ResponseDet(temp)==1)
			{
				ErrType=0;
				break;
			}//��ʱǰ��⵽��ok
			
			if(ResponseDet(temp)==2)
			{
				ErrType=2;
				break;
			}//��ʱǰ���ܵ�ERROR
		}
		memset(temp,0,sizeof(u8)*100);
		flag=0;
		delay_ms(1);
		ErrType=1;//Ĭ���ǳ�ʱ����ģ�����okȥ����
	}//1sû�м�⵽��ǿ������,��ErrType=1
	
	return ErrType;
}



u8 E17_SendMsg(u8 which,u8 value)
{
	switch(which)
	{
		case CMD_X_PARAM:printf1("%x%x%x%x%x%x%x%x%x%x%x",0xD0,0x07,0x56,0x78,0x22,0x58,0x22,0x3A,0x22,value,0x22);break;
		case CMD_Y_PARAM:printf1("%x%x%x%x%x%x%x%x%x%x%x",0xD0,0x07,0x56,0x78,0x22,0x59,0x22,0x3A,0x22,value,0x22);break;
		case CMD_S_PARAM:printf1("%x%x%x%x%x%x%x%x%x%x%x",0xD0,0x07,0x56,0x78,0x22,0x53,0x22,0x3A,0x22,value,0x22);break;
		case CMD_D_PARAM:printf1("%x%x%x%x%x%x%x%x%x%x%x",0xD0,0x07,0x56,0x78,0x22,0x44,0x22,0x3A,0x22,value,0x22);break;
		default:break;
	}
	return 1;
}

#endif

