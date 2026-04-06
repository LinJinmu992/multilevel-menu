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
//	Timer_Init(); 这是屏幕刷新的代码，可能我代码写的有点烂，刷新的时候闪的我太难受了，我就给注释了，目前刷新时间为1s
	
	while(1)
		{
		
		}
}
