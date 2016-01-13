#ifndef _PLANEAUTO_H_
#define _PLANEAUTO_H_

#include "../../SYSTEM/sys/sys.h"

#define ACCE_PROPORTION 	0		//通道值与上升下降速度的比值
#define YAW_PROPORTION 		0		//通道值与偏航速度之间的比值
#define	ROLL_PROPORTION   0		//通道值与翻滚速度的比值
#define PITCH_RPOPORTION	0		//通道值与俯仰速度之间的比值

#define THE_ERR_X 0		//误差范围圈X，未测试，测试后填参数
#define THE_ERR_Y 0		//误差范围圈Y，未测试，测试后填参数

#define __ACCE 1
#define __YAW 2
#define __ROLL 3
#define __PITCH 4

/*******************************************************/
void Plane_Up(long UpSpeed);					//油门，UpSpeed海拔上升速度
void Plane_Down(long DownSpeed);			//油门，DownSpeed海拔下降速度
void Plane_Yaw(long YawSpeed);				//偏航，YawSpeed偏航速度 
void Plane_Roll(long RollSpeed);			//翻滚，RollSpeed翻滚速度/左右走
void Plane_Pitch(long PitchSpeed);		//俯仰角，PitchSpeed/前后走


u8 Plane_PID(int X_value,int Y_value);//飞行器自适应，使得物体总是在误差圈内
void Plane_UNLOCK(void);
void Plane_LOCK(void);
u8 Plane_LAUNCH(void);

#endif

