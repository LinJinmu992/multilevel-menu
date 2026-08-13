#include "stm32f10x.h" // Device header
#include "menu.h"
#include "Delay.h"

/* Public function implementations ----------------------------------------- */

void KeyEXTI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line4 | EXTI_Line6;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		Delay_ms(10);
		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
			Menu_HandleEvent(MENU_EVENT_CONFIRM);
		}
	
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) == SET)
	{
		Delay_ms(10);
		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
		{
			Menu_HandleEvent(MENU_EVENT_NEXT);
		}
		
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		Delay_ms(10);
		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
		{
			Menu_HandleEvent(MENU_EVENT_PREVIOUS);
		}
		
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
