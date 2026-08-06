#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "MenuIP.h"
#include "MenuData.h"
uint16_t Getvalue (uint16_t Value);

MenuIP IP = MENU_IP_ROOT;//每个十六进制位分别保存三级菜单路径和光标位置

uint8_t Comfirm_Status = 1;//确认使能

uint16_t P_value = 0;
uint16_t I_value = 0;
uint16_t D_value = 0;//仅测试用所以直接在这里声明了


void MenuDisplay (void)//菜单的显示部分，我将菜单的显示部分和整个菜单的主体框架函数分开以方便修改，建议先从下面的主体框架函数开始看，显示部分的逻辑就是根据IP的值得到目前菜单的位置，然后显示相应的内容
{
	uint8_t Line;
	Line = MenuIP_GetCursor(IP);
	
	OLED_Clear();
	
	OLED_ShowChar(Line, 1, '>');
	
	if(MenuIP_GetDepth(IP) == 0)
	{
		OLED_ShowString(1, 2, "adc");
		OLED_ShowString(2, 2, "error");
		OLED_ShowString(3, 2, "pid");
		OLED_ShowString(4, 2, "Ciallo!");
	}else if(MenuIP_GetDepth(IP) == 1)
				{
					uint8_t Menu;
					Menu = MenuIP_GetItem(IP, 1);
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
				}else if(MenuIP_GetDepth(IP) == 2)
				{
					uint8_t Menu;
					Menu = MenuIP_GetItem(IP, 2);
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
uint8_t ItemCount;
MenuItemType ItemType;
//Operate为0时，无操作；Operate为1时，执行加一操作；Operate为2时，执行减一操作；Operate为3时，执行确认操作，按键通过外部中断函数调用这个函数  
		switch (Operate) {
        case 1: // 加1操作
            /* 从页面表获取实际项目数量，再执行循环向下移动 */
            ItemCount = MenuData_GetItemCount(IP);
            IP = MenuIP_MoveNext(IP, ItemCount);
            break;
            
        case 2: // 减1操作
            /* 从页面表获取实际项目数量，再执行循环向上移动 */
            ItemCount = MenuData_GetItemCount(IP);
            IP = MenuIP_MovePrevious(IP, ItemCount);
            break;
            
        case 3: // 确认操作
			if(Comfirm_Status)	//这里变量的用途会在特殊功能区说明
						{
							/* 由菜单说明表决定当前项目按下确认后的行为 */
							ItemType = MenuData_GetCurrentItemType(IP);
							switch (ItemType)
							{
								case MENU_ITEM_SUBMENU:
								case MENU_ITEM_VALUE:
									/* 普通子菜单和参数项都需要进入下一级 */
									IP = MenuIP_Enter(IP);
									break;

								case MENU_ITEM_BACK:
									/* 返回项清除当前最深一级菜单路径 */
									IP = MenuIP_Back(IP);
									break;

								case MENU_ITEM_ACTION:
									/* 功能项预留给后续功能回调，当前不改变IP */
								case MENU_ITEM_NONE:
								default:
									break;
							}
						}
            break;
            
//        default: // 无效操作
//            return; // 直接退出 //这边是我一开始忘记了函数遇到return会直接终止，但我觉得吧default写进去是一个很好的习惯所以用注释将其保留
    }
		
//此外行往下为特殊功能区，当遇到主体框架代码无法实现的功能时（如对某个值进行更改）可通过特殊功能区单独写相关的功能代码

		if((MenuIP_GetItem(IP, 2) != 0) && (MenuIP_GetItem(IP, 1) == 3))
		{
			Comfirm_Status = 0;	//确认操作失能
			
			if(MenuIP_GetItem(IP, 2) == 1)	//通过IP判断菜单是否在P值的更改菜单
				P_value = Getvalue(P_value);
			
			if(MenuIP_GetItem(IP, 2) == 2)
				I_value = Getvalue(I_value);
			
			if(MenuIP_GetItem(IP, 2) == 3)
				D_value = Getvalue(D_value);
			
			Comfirm_Status = 1;
		}
		
//特殊功能区结束
		
		MenuDisplay();
}
//数值更改的程序
uint16_t Getvalue (uint16_t Value)
{
	if((MenuIP_GetCursor(IP) == 2) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
		Value ++;
	if((MenuIP_GetCursor(IP) == 3) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
		Value --;
	if((MenuIP_GetCursor(IP) == 4) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0))
	{
		IP = MenuIP_Make(3, 0, 0, 1);
	}
	return Value;
}
