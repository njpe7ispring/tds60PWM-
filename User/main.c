#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Encoder.h"

uint8_t KeyNum;		//定义用于接收按键键码的变量
int8_t Speed;		//定义速度变量

int8_t Num;			//定义待被旋转编码器调节的变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Motor_Init();		//直流电机初始化
	//Key_Init();			//按键初始化   控制范围较大，每次改变20%
	Encoder_Init();		//旋转编码器初始化   每次改变1%
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Speed:");		//1行1列显示字符串Speed:
	/*显示静态字符串*/
	OLED_ShowString(2, 1, "Num:");			//2行1列显示字符串Num:      Num控制在（-100-100）因为速度有上限低于或者高于极限都不在变动
	
	while (1)
	{
		
		Num += Encoder_Get();				//获取自上此调用此函数后，旋转编码器的增量值，并将增量值加到Num上
		OLED_ShowSignedNum(2, 5, Num, 5);	//显示Num
		Speed = Num;
//		KeyNum = Key_GetNum();				//获取按键键码
//		if (KeyNum == 1)					//按键1按下
//		{
//			Speed += 20;					//速度变量自增20
//			if (Speed > 100)				//速度变量超过100后
//			{
//				Speed = -100;				//速度变量变为-100
//											//此操作会让电机旋转方向突然改变，可能会因供电不足而导致单片机复位
//											//若出现了此现象，则应避免使用这样的操作
//			}
//		}
		if (Speed < -100)					//按键1按下
		{
			Speed = -100;				//速度变量变为-100为极限
		}
		if (Speed > 100)					//按键1按下
		{
			Speed = 100;				//速度变量变为-100为极限
		}
		Motor_SetSpeed(Speed);				//设置直流电机的速度为速度变量
		OLED_ShowSignedNum(1, 7, Speed, 3);	//OLED显示速度变量
	}
}
