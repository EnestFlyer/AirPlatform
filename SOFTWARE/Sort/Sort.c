#include "../../SOFTWARE/Sort/Sort.h"
#include "../../SYSTEM/sys/sys.h"

static int FindMin(int before[],int head,int length)
{
	int loop=length-head+1;
	int i=0;
	int min=before[head];
	for(i=0;i<loop;i++)
	{
		if(min>=before[head])
		{
			min=before[head];	
		}
		head++;	
	}
	return min;
}

static int Search(int before[],int data,int length)
{
	int i=0;
	for(i=0;i<length+1;i++)
	{
		if(data==before[i])
		{
			return i;
		}
	}
}

u8 SimpleSelect(int before[],int length)
{
	int i=0;
	int tmp=0;
	int min=0;
	int loc=0;
	
	for(i=0;i<length+1;i++)
	{
		min=FindMin(before,i+1,length);
		loc=Search(before,min,length);
		if(before[i]>=min)
		{
			tmp=before[i];
			before[i]=min;
			before[loc]=tmp;
		}
	}
	return 1;
}



