#include "menu_view.h"
#include "MenuData.h"
#include "menu_port.h"

/* Private function declarations ------------------------------------------- */

static void ShowPageItems(MenuIP ip);

/* Public function implementations ----------------------------------------- */

void MenuView_Render(MenuIP ip, uint16_t p, uint16_t i, uint16_t d)
{
    uint8_t depth = MenuIP_GetDepth(ip);
    uint8_t page_item;

    MenuPort_Clear();
    MenuPort_ShowChar(MenuIP_GetCursor(ip), 1U, '>');
    ShowPageItems(ip);

    if ((depth == 1U) && (MenuIP_GetItem(ip, 1U) == 3U))
    {
        MenuPort_ShowNum(1U, 15U, p, 2U);
        MenuPort_ShowNum(2U, 15U, i, 2U);
        MenuPort_ShowNum(3U, 15U, d, 2U);
    }
    else if ((depth == 2U) && (MenuIP_GetItem(ip, 1U) == 3U))
    {
        page_item = MenuIP_GetItem(ip, 2U);
        if (page_item == 1U) MenuPort_ShowNum(1U, 15U, p, 2U);
        else if (page_item == 2U) MenuPort_ShowNum(1U, 15U, i, 2U);
        else if (page_item == 3U) MenuPort_ShowNum(1U, 15U, d, 2U);
    }
}

/* Private function implementations ---------------------------------------- */

static void ShowPageItems(MenuIP ip)
{
    uint8_t item;
    uint8_t item_count = MenuData_GetItemCount(ip);

    for (item = 1U; item <= item_count; item++)
    {
        const char *label = MenuData_GetItemLabel(ip, item);
        if (label != 0)
        {
            MenuPort_ShowString(item, 2U, label);
        }
    }
}
