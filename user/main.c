#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "menu.h"
#include "EXTI.h"
#include "TIM.h"

int main(void)
{
	OLED_Init();
	KeyEXTI_Init();
//	Timer_Init(); 这是屏幕刷新的代码，由于我使用的是无缓存功能的屏幕显示源码,
				//所以会出现屏幕闪烁，由于是一年前的工程加之我好久没写单片机相关的代码了（一句话就是懒了）
				//所以就不改了，目前刷新时间为1s
	
	while(1)
		{
		
		}
}
