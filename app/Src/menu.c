#include "menu.h"
#include "MenuData.h"
#include "MenuIP.h"
#include "menu_port.h"
#include "menu_view.h"

static MenuIP IP = MENU_IP_ROOT;
static uint16_t P_value;
static uint16_t I_value;
static uint16_t D_value;

void MenuDisplay(void)
{
    MenuView_Render(IP, P_value, I_value, D_value);
}

static uint16_t GetValue(uint16_t value)
{
    if (!MenuPort_IsConfirmPressed()) return value;
    if (MenuIP_GetCursor(IP) == 2) value++;
    else if (MenuIP_GetCursor(IP) == 3) value--;
    else if (MenuIP_GetCursor(IP) == 4) IP = MenuIP_Make(3, 0, 0, 1);
    return value;
}

void Menu_Info(uint8_t operate)
{
    uint8_t count;
    MenuItemType type;

    if (operate == 1)
    {
        count = MenuData_GetItemCount(IP);
        IP = MenuIP_MoveNext(IP, count);
    }
    else if (operate == 2)
    {
        count = MenuData_GetItemCount(IP);
        IP = MenuIP_MovePrevious(IP, count);
    }
    else if (operate == 3)
    {
        type = MenuData_GetCurrentItemType(IP);
        if ((type == MENU_ITEM_SUBMENU) || (type == MENU_ITEM_VALUE)) IP = MenuIP_Enter(IP);
        else if (type == MENU_ITEM_BACK) IP = MenuIP_Back(IP);
    }

    if ((MenuIP_GetItem(IP, 2) != 0) && (MenuIP_GetItem(IP, 1) == 3))
    {
        if (MenuIP_GetItem(IP, 2) == 1) P_value = GetValue(P_value);
        else if (MenuIP_GetItem(IP, 2) == 2) I_value = GetValue(I_value);
        else if (MenuIP_GetItem(IP, 2) == 3) D_value = GetValue(D_value);
    }

    MenuDisplay();
}
