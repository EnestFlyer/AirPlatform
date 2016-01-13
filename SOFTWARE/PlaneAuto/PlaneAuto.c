////////////////////////////////////////////////////////////////
//用USART 3做无线串口
//
////////////////////////////////////////////////////////////////
#include "../../SOFTWARE/PlaneAuto/PlaneAuto.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SYSTEM/delay/delay.h"
#include  "string.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"


void Plane_Up(long UpSpeed)
{
	
}//油门，UpSpeed海拔上升速度
void Plane_Down(long DownSpeed)
{
	
}//油门，DownSpeed海拔下降速度
void Plane_Yaw(long YawSpeed)
{
	
}//偏航，YawSpeed偏航速度 
void Plane_Roll(long RollSpeed)
{	
	
}//翻滚，RollSpeed翻滚速度/左右走
void Plane_Pitch(long PitchSpeed)
{
	
}//俯仰角，PitchSpeed/前后走


void Plane_UNLOCK()
{
	SetChannelValue(__ACCE,1100);
	SetChannelValue(__YAW,1950);
	SetChannelValue(__ROLL,1100);
	SetChannelValue(__PITCH,1100);
}


void Plane_LOCK()
{
	SetChannelValue(__ACCE,1100);
	SetChannelValue(__YAW,1100);
	SetChannelValue(__ROLL,1950);
	SetChannelValue(__PITCH,1100);
}

void Plane_LAND()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////
extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];
u8 FlagOfCatch=0;

u8 Plane_LAUNCH()
{
	int len=0;
	int t=0;
	u8 flag=0;//接满标志，置位为接满
	u8 temp[100]={0};//缓冲池
	char command='O';//命令字
	
	SetChannelValue(__ACCE,1600);//缓慢上升
	delay_ms(1000);delay_ms(1000);
	SetChannelValue(__YAW,1600);
	while(!FlagOfCatch)
	{
		if(USART_RX3_STA&0x8000)
		{					   
			len=USART_RX3_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=Rx3Buf[t];
				while((USART3->SR&0X40)==0);//等待发送结束
			}
			flag=1;
			USART_RX3_STA=0;
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='S')
			{
				printf1("S=%d\n",ValueOfMea(temp));//for test
				FlagOfCatch=ValueOfMea(temp);
			}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}
	SetChannelValue(__PITCH,1600);
	SetChannelValue(__ACCE,1500);
	return 1;
}



u8 Plane_PID(int X_value,int Y_value)
{
	if((X_value<THE_ERR_X)&&(Y_value<THE_ERR_Y))
	{
		
	}//在范围圈之内,以小速度收敛
	else
	{
		
	}//在范围圈之外，以大速度收敛
	return 1;
}

