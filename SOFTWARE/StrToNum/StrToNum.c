//////////////////////////////////////////////////////////////////
//模块功能：用于识别远端发来的指令
//帧格式 "A/Y/R/P/C/S":"Num"
//A->ACCE
//Y->YAW
//R->ROLL
//P->PITCH
//C->COMMAND
//S->STATUS

//不如地面端去处理电阻数据，直接传递x偏移量和y偏移量即可
//"X":"X_Value"
//"Y":"Y_Value"

//////////////////////////////////////////////////////////////////

#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../SYSTEM/sys/sys.h"
#include "string.h"

/////////////////////////////////////////////////////////////////
//函数功能：提取单条指令中的命令字
//返回：单条指令中的命令字
//参数：u8 *temp 传入指令数组的指针
/////////////////////////////////////////////////////////////////
char TempOrPressure(u8 *temp)
{
	u8 i=0;
	u8 counter=0;
	for(i=0;*(temp+i)!=0x0A;i++)
	{
		if(*(temp+i)=='"')
		{
			counter++;
		}
		if(counter==1)
			return *(temp+i+1);
	}	
}

static long powerTen(u8 power)
{
	if(power==1)
		return 10;
	else
		return 10*powerTen(power-1);
}

/////////////////////////////////////////////////////////////////
//函数功能：提取单条指令中的数值
//返回：单条指令中的数值
//参数：u8 *temp 传入指令数组的指针
/////////////////////////////////////////////////////////////////
long ValueOfMea(u8 *temp)
{
	u8 i=0;
	u8 j=0;
	u8 counter=0;
	u8 len=0;
	char NumToString[20];
	long value=0;
	for(i=0;*(temp+i)!=0x0A;i++)
	{
		if(*(temp+i)=='"')
		{
			counter++;
		}
		if(counter>=3)
		{
			if(*(temp+i)!='"')
			{
				NumToString[j]=*(temp+i);
				j++;
			}
			else if(counter==3)
			{
				continue;
			}
			else 
				break;
		}
	}
	NumToString[j]='\0';
	len=strlen(NumToString);
  
	for(i=0,j=len-1;i<len;i++,j--)
	{
		value+=(NumToString[j]-48)*powerTen(len-j);
	}
	
	return value/10;
}
