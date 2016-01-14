#include "../../SOFTWARE/Sort/Sort.h"
#include "../../SYSTEM/sys/sys.h"

void Bubble_Sort(int num[], int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; i + j < n - 1; j++)
        {
            if(num[j] > num[j + 1])
            {
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
    return;
}


