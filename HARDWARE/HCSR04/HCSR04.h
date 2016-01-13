#ifndef _HCSR04_H_
#define _HCSR04_H_

#include "../../SYSTEM/sys/sys.h"

#define TRIG PAout(4) 
#define ECHO PAin(1)

void HCSR04_Init(void);
static float HCSR04_GetDistance(void);
int HCSR04_GetDistance_Filter(void);

#endif
