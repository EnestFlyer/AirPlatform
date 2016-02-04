#ifndef __E17_TTL500_H_
#define __E17_TTL500_H_

#include "../../SYSTEM/sys/sys.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"

#ifdef __COMMAND_MODE
#define CMD_X_PARAM 1
#define CMD_Y_PARAM 2
#define CMD_S_PARAM 3
#define CMD_D_PARAM 4
#define CMD_G_PARAM 5

u8 ResponseDet(char *str);
u8 E17_SelfTest(void);
u8 E17_SendMsg(u8 which,u8 value);


#endif

#endif

