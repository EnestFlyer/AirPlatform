#ifndef _HCSR04_H_
#define _HCSR04_H_

#include "../../SYSTEM/sys/sys.h"

#define TRIG PAout(4) 
#define ECHO PAin(1)

#define TRIG_GROUND PFout(1)
#define ECHO_GROUND PFin(2)

void HCSR04_Init(void);
int HCSR04_GetDistance(void);
int HCSR04_GetDistance_Filter(void);

int GROUND_GetDistance(void);
int GROUND_GetDistance_Filter(void);

#endif

