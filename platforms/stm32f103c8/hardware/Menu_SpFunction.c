#include "stm32f10x.h"                  // Device header

uint16_t GetValue (uint16_t Value)
{
	if(((IP & MaskL) == 0x0002) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
				P_value ++;
			if(((IP & MaskL) == 0x0003) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
				P_value --;
			if(((IP & MaskL) == 0x0004) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
			{
				IP = 0x0031;
			}
}