#include "menu.h"
#include "MenuData.h"
#include "MenuIP.h"
#include "menu_view.h"

/* Private variables -------------------------------------------------------- */

static MenuIP IP = MENU_IP_ROOT;
static uint16_t P_value;
static uint16_t I_value;
static uint16_t D_value;

/* Private function declarations ------------------------------------------- */

static uint16_t EditValue(uint16_t value);

/* Public function implementations ----------------------------------------- */

void MenuDisplay(void)
{
    MenuView_Render(IP, P_value, I_value, D_value);
}

void Menu_HandleEvent(MenuEvent event)
{
    uint8_t count;
    MenuItemType type;

    if (event == MENU_EVENT_NEXT)
    {
        count = MenuData_GetItemCount(IP);
        IP = MenuIP_MoveNext(IP, count);
    }
    else if (event == MENU_EVENT_PREVIOUS)
    {
        count = MenuData_GetItemCount(IP);
        IP = MenuIP_MovePrevious(IP, count);
    }
    else if (event == MENU_EVENT_CONFIRM)
    {
        type = MenuData_GetCurrentItemType(IP);
        if ((type == MENU_ITEM_SUBMENU) || (type == MENU_ITEM_VALUE)) IP = MenuIP_Enter(IP);
        else if (type == MENU_ITEM_BACK) IP = MenuIP_Back(IP);
    }
    else
    {
        return;
    }

    if ((event == MENU_EVENT_CONFIRM) &&
        (MenuIP_GetItem(IP, 2) != 0) &&
        (MenuIP_GetItem(IP, 1) == 3))
    {
        if (MenuIP_GetItem(IP, 2) == 1) P_value = EditValue(P_value);
        else if (MenuIP_GetItem(IP, 2) == 2) I_value = EditValue(I_value);
        else if (MenuIP_GetItem(IP, 2) == 3) D_value = EditValue(D_value);
    }

    MenuDisplay();
}

/* Private function implementations ---------------------------------------- */

static uint16_t EditValue(uint16_t value)
{
    if (MenuIP_GetCursor(IP) == 2) value++;
    else if (MenuIP_GetCursor(IP) == 3) value--;
    else if (MenuIP_GetCursor(IP) == 4) IP = MenuIP_Make(3, 0, 0, 1);
    return value;
}
