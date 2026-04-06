#include "stm32f10x.h"                  // Device header
#include "OLED.h"
uint16_t Getvalue (uint16_t Value);

uint16_t IP = 0x0001;//我给每一个菜单都分配了一个IP，为了便于解释，从左到右依次称为左一左二右二右一。理论上来说这个菜单框架一级可以容纳16个菜单，总计65536个菜单

uint16_t MaskL = 0x000F;//光标位置掩码
uint16_t Mask1 = 0x00F0;//一级菜单掩码
uint16_t Mask2 = 0x0F00;//二级菜单掩码
uint16_t Mask3 = 0xF000;//三级菜单掩码

uint8_t Comfirm_Status = 1;//确认使能

uint16_t P_value = 0;
uint16_t I_value = 0;
uint16_t D_value = 0;//仅测试用所以直接在这里声明了


void MenuDisplay (void)//菜单的显示部分，我将菜单的显示部分和整个菜单的主体框架函数分开以方便修改，建议先从下面的主体框架函数开始看，显示部分的逻辑就是根据IP的值得到目前菜单的位置，然后显示相应的内容
{
	uint8_t Line;
	Line = IP & MaskL;
	
	OLED_Clear();
	
	OLED_ShowChar(Line, 1, '>');
	
	if((IP & Mask1) == 0)
	{
		OLED_ShowString(1, 2, "adc");
		OLED_ShowString(2, 2, "error");
		OLED_ShowString(3, 2, "pid");
		OLED_ShowString(4, 2, "Ciallo!");
	}else if((IP & Mask2) == 0)
				{
					uint8_t Menu;
					Menu = (IP & Mask1) >> 4;
					switch (Menu){
						case 1:
							OLED_ShowString(1, 2, "adc1");
							OLED_ShowString(2, 2, "adc2");
							OLED_ShowString(3, 2, "adc3");
							OLED_ShowString(4, 2, "exit");
							break;
						
						case 2:
							OLED_ShowString(1, 2, "error1");
							OLED_ShowString(2, 2, "error2");
							OLED_ShowString(3, 2, "error3");
							OLED_ShowString(4, 2, "exit");
							break;
						
						case 3:
							OLED_ShowString(1, 2, "P");
							OLED_ShowNum(1, 15, P_value, 2);
							OLED_ShowString(2, 2, "I");
							OLED_ShowNum(2, 15, I_value, 2);
							OLED_ShowString(3, 2, "D");
							OLED_ShowNum(3, 15, D_value, 2);
							OLED_ShowString(4, 2, "exit");
							break;
						
						/*case 4:
							OLED_ShowString(1, 2, "C");
							OLED_ShowString(2, 2, "I");
							OLED_ShowString(3, 2, "A");
							OLED_ShowString(4, 2, "L");
							break;
						*/
					}
				}else if((IP & Mask3) == 0)
				{
					uint8_t Menu;
					Menu = (IP & Mask2) >> 8;
					switch (Menu){
						case 1:
							OLED_ShowString(1, 2, "P");
							OLED_ShowNum(1, 15, P_value, 2);
							OLED_ShowString(2, 2, "+");	
							OLED_ShowString(3, 2, "-");
							//OLED_ShowHexNum(4, 2, IP, 4);
							OLED_ShowString(4, 2, "Comfirm");
							break;
						
						case 2:
							OLED_ShowString(1, 2, "I");
							OLED_ShowNum(1, 15, I_value, 2);
							OLED_ShowString(2, 2, "+");	
							OLED_ShowString(3, 2, "-");
							//OLED_ShowHexNum(4, 2, IP, 4);
							OLED_ShowString(4, 2, "Comfirm");
							break;
						
						case 3:
							OLED_ShowString(1, 2, "D");
							OLED_ShowNum(1, 15, D_value, 2);
							OLED_ShowString(2, 2, "+");	
							OLED_ShowString(3, 2, "-");
							//OLED_ShowHexNum(4, 2, IP, 4);
							OLED_ShowString(4, 2, "Comfirm");
							break;
						
						/*case 4:
							OLED_ShowString(1, 2, "C");
							OLED_ShowString(2, 2, "I");
							OLED_ShowString(3, 2, "A");
							OLED_ShowString(4, 2, "L");
							break;
						*/
					}
				}
	
}

//由此往下是菜单的主体框架
void Menu_Info(uint8_t Operate) {
//Operate为0时，无操作；Operate为1时，执行加一操作；Operate为2时，执行减一操作；Operate为3时，执行确认操作，按键通过外部中断函数调用这个函数  
		switch (Operate) {
        case 1: // 加1操作
            IP++;
            if ((IP & MaskL) > 0x0004) IP -= 4;	//我将IP的右一用作确认光标的位置
            break;
            
        case 2: // 减1操作
            IP--;
            if ((IP & MaskL) == 0) IP += 4;
            break;
            
        case 3: // 确认操作
            if(Comfirm_Status)	//这里变量的用途会在特殊功能区说明
						{
							if (((IP & Mask1) == 0) && ((IP & MaskL) != 4)) {							//关于IP：在声明时已被初始化为0x0001，即位于主菜单，光标位置在第一行，此时如果我点击确认按钮
								IP = ((IP & 0xFFF0) | 0x0001) | ((IP & MaskL) << 4);				//函数会判断右二是否为0，若为0说明此时并非主菜单界面（这个稍后会说明），目前只说明当IP为0x0001
							} else if (((IP & Mask1) == 0) && ((IP & MaskL) == 4)) {			//时的情况，此时右二位置为0，右一的数字会被移位至右二并被初始化为1，即0x0001变为0x0011,0x0002变为0x0021
									IP = 0x0001;																							//若此时右一（光标位置）为4，会返回上一级，（若在主菜单光标会回到第一行）
							} else if (((IP & Mask2) == 0) && ((IP & MaskL) != 4)) {			//接着上面的判断右二是否为0继续说，若不为0则说明不在主菜单位置，则会去判断是否在一级菜单（即左二为0）
									IP = ((IP & 0xFFF0) | 0x0001) | ((IP & MaskL) << 8);			//后面以此类推即可，若需要不止三级菜单，可将光标的位置单独用变量声明，则IP又可以有一位可用，也可通过将IP设置为32位解决（不过也不会有这么多级菜单吧）	
							} else if (((IP & Mask2) == 0) && ((IP & MaskL) == 4)) {			
									IP = IP & ~Mask1;
							} else if (((IP & Mask3) == 0) && ((IP & MaskL) == 4)) {			//目前来说有点抽象，那就来说说IP的读法：右一为光标位置，正如上面所说当按确认键，右一的值会被移位至不同的位置
									IP = IP & ~Mask2;																					//但右一不仅可以用来记录光标位置，也可以记录菜单的位置，比如为2时可表示为从上到下第二个菜单
							}																															//那么读起来就很方便了，比如IP = 0x3221，意思为光标位置为1，目前菜单是主菜单中的第二个菜单中的第二个菜单中的第三个菜单
						}
            break;
            
//        default: // 无效操作
//            return; // 直接退出 //这边是我一开始忘记了函数遇到return会直接终止，但我觉得吧default写进去是一个很好的习惯所以用注释将其保留
    }
		
//此行往下均为补丁区 			上述主体的代码只能满足前进后退的功能，那么当遇到下一级没有菜单的时候就需要通过补丁进行修正
		
		if(((IP & Mask2) != 0) && ((IP & Mask1) == 0x0010))
		{
			IP = 0x0011;
		}//取消IP为0x xx1x的下一级菜单
		
		if(((IP & Mask2) != 0) && ((IP & Mask1) == 0x0020))
		{
			IP = 0x0021;
		}//取消IP为0x xx2x的下一级菜单
		
//		if(((IP & Mask2) != 0) && ((IP & Mask1) == 0x0030))
//		{
//			IP = 0x0031;
//		}//取消IP为0x xx3x的下一级菜单

//补丁区结束    
		
//此外行往下为特殊功能区，当遇到主体框架代码无法实现的功能时（如对某个值进行更改）可通过特殊功能区单独写相关的功能代码

		if(((IP & Mask2) != 0) && ((IP & Mask1) == 0x0030))
		{
			Comfirm_Status = 0;	//确认操作失能
			
			if((IP & Mask2) == 0x0100)	//通过IP判断菜单是否在P值的更改菜单
				P_value = Getvalue(P_value);
			
			if((IP & Mask2) == 0x0200)
				I_value = Getvalue(I_value);
			
			if((IP & Mask2) == 0x0300)
				D_value = Getvalue(D_value);
			
			Comfirm_Status = 1;
		}
		
//特殊功能区结束
		
		MenuDisplay();
}
//数值更改的程序
uint16_t Getvalue (uint16_t Value)
{
	if(((IP & MaskL) == 0x0002) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
		Value ++;
	if(((IP & MaskL) == 0x0003) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
		Value --;
	if(((IP & MaskL) == 0x0004) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
	{
		IP = 0x0031;
	}
	return Value;
}
