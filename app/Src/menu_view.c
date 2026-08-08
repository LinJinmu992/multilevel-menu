#include "menu_view.h"
#include "menu_port.h"

static void ShowValuePage(char name, uint16_t value)
{
    MenuPort_ShowChar(1, 2, name);
    MenuPort_ShowNum(1, 15, value, 2);
    MenuPort_ShowString(2, 2, "+");
    MenuPort_ShowString(3, 2, "-");
    MenuPort_ShowString(4, 2, "Confirm");
}

void MenuView_Render(MenuIP ip, uint16_t p, uint16_t i, uint16_t d)
{
    uint8_t depth = MenuIP_GetDepth(ip);
    uint8_t item;

    MenuPort_Clear();
    MenuPort_ShowChar(MenuIP_GetCursor(ip), 1, '>');

    if (depth == 0)
    {
        MenuPort_ShowString(1, 2, "adc");
        MenuPort_ShowString(2, 2, "error");
        MenuPort_ShowString(3, 2, "pid");
        MenuPort_ShowString(4, 2, "Ciallo!");
        return;
    }

    if (depth == 1)
    {
        item = MenuIP_GetItem(ip, 1);
        if (item == 1)
        {
            MenuPort_ShowString(1, 2, "adc1");
            MenuPort_ShowString(2, 2, "adc2");
            MenuPort_ShowString(3, 2, "adc3");
        }
        else if (item == 2)
        {
            MenuPort_ShowString(1, 2, "error1");
            MenuPort_ShowString(2, 2, "error2");
            MenuPort_ShowString(3, 2, "error3");
        }
        else if (item == 3)
        {
            MenuPort_ShowChar(1, 2, 'P'); MenuPort_ShowNum(1, 15, p, 2);
            MenuPort_ShowChar(2, 2, 'I'); MenuPort_ShowNum(2, 15, i, 2);
            MenuPort_ShowChar(3, 2, 'D'); MenuPort_ShowNum(3, 15, d, 2);
        }
        MenuPort_ShowString(4, 2, "exit");
        return;
    }

    if (depth == 2)
    {
        item = MenuIP_GetItem(ip, 2);
        if (item == 1) ShowValuePage('P', p);
        else if (item == 2) ShowValuePage('I', i);
        else if (item == 3) ShowValuePage('D', d);
    }
}
