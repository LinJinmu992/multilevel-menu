#ifndef __MENU_DATA_H
#define __MENU_DATA_H

#include "MenuIP.h"

typedef enum
{
    MENU_ITEM_NONE = 0,
    MENU_ITEM_SUBMENU,
    MENU_ITEM_ACTION,
    MENU_ITEM_VALUE,
    MENU_ITEM_BACK
} MenuItemType;

uint8_t MenuData_GetItemCount(MenuIP ip);
const char *MenuData_GetItemLabel(MenuIP ip, uint8_t item);
MenuItemType MenuData_GetCurrentItemType(MenuIP ip);

#endif
