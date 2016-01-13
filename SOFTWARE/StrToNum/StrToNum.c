//////////////////////////////////////////////////////////////////
//ģ�鹦�ܣ�����ʶ��Զ�˷�����ָ��
//֡��ʽ "A/Y/R/P/C/S":"Num"
//A->ACCE
//Y->YAW
//R->ROLL
//P->PITCH
//C->COMMAND
//S->STATUS

//��������ȥ�����������ݣ�ֱ�Ӵ���xƫ������yƫ��������
//"X":"X_Value"
//"Y":"Y_Value"

//////////////////////////////////////////////////////////////////

#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../SYSTEM/sys/sys.h"
#include "string.h"

/////////////////////////////////////////////////////////////////
//�������ܣ���ȡ����ָ���е�������
//���أ�����ָ���е�������
//������u8 *temp ����ָ�������ָ��
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
//�������ܣ���ȡ����ָ���е���ֵ
//���أ�����ָ���е���ֵ
//������u8 *temp ����ָ�������ָ��
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