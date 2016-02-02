#include "../../HARDWARE/E17_TTL500/E17_TTL500.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "string.h"
#include "stdlib.h"
//飞机端，既是本机的地址为0x2345
//地面站的地址为0x5678

#ifdef __COMMAND_MODE

extern u16 USART_RX1_STA;

u8 ResponseDet(char *str)
{
	if(strcmp(str,"OK\r\n")==0)//相同
		return 1;
	else if(strcmp(str,"ERROR\r\n")==0)
		return 2;
	else 
		return 0;
}

u8 E17_SelfTest()//做链路自检用
{
	int i=0;
	int len=0;
	char temp[100];
	u8 t=0;
	u8 flag=0;
	u8 ErrType=0;//0为无错误，1为超时仍未接受到OK,2为接受到ERROR
	
	printf1("%x%x%x",0xC2,0xC2,0xC2);//握手命令，成功发送OK\r\n,准备接受ok
	for(i=0;i<1000;i++)
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
		}//接送E17模块的反馈
		
		if(flag==1)
		{
			if(ResponseDet(temp)==1)
			{
				ErrType=0;
				break;
			}//超时前检测到了ok
			
			if(ResponseDet(temp)==2)
			{
				ErrType=2;
				break;
			}//超时前接受到ERROR
		}
		memset(temp,0,sizeof(u8)*100);
		flag=0;
		delay_ms(1);
		ErrType=1;//默认是超时错误的，除非ok去除了
	}//1s没有检测到就强行跳过,置ErrType=1
	
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

