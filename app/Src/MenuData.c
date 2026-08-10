#include "MenuData.h"

#define MENU_PAGE_MAX_ITEMS 4U

typedef struct
{
    const char *label;
    MenuItemType type;
} MenuItemDefinition;

typedef struct
{
    MenuIP path;
    uint8_t item_count;
    MenuItemDefinition items[MENU_PAGE_MAX_ITEMS];
} MenuPageDefinition;

static const MenuPageDefinition MenuPages[] =
{
    {0x0000, 4, {{"adc", MENU_ITEM_SUBMENU},
                 {"error", MENU_ITEM_SUBMENU},
                 {"pid", MENU_ITEM_SUBMENU},
                 {"Ciallo!", MENU_ITEM_ACTION}}},

    {0x0010, 4, {{"adc1", MENU_ITEM_ACTION},
                 {"adc2", MENU_ITEM_ACTION},
                 {"adc3", MENU_ITEM_ACTION},
                 {"exit", MENU_ITEM_BACK}}},

    {0x0020, 4, {{"error1", MENU_ITEM_ACTION},
                 {"error2", MENU_ITEM_ACTION},
                 {"error3", MENU_ITEM_ACTION},
                 {"exit", MENU_ITEM_BACK}}},

    {0x0030, 4, {{"P", MENU_ITEM_VALUE},
                 {"I", MENU_ITEM_VALUE},
                 {"D", MENU_ITEM_VALUE},
                 {"exit", MENU_ITEM_BACK}}},

    {0x0130, 4, {{"P", MENU_ITEM_ACTION},
                 {"+", MENU_ITEM_ACTION},
                 {"-", MENU_ITEM_ACTION},
                 {"Confirm", MENU_ITEM_BACK}}},
    {0x0230, 4, {{"I", MENU_ITEM_ACTION},
                 {"+", MENU_ITEM_ACTION},
                 {"-", MENU_ITEM_ACTION},
                 {"Confirm", MENU_ITEM_BACK}}},
    {0x0330, 4, {{"D", MENU_ITEM_ACTION},
                 {"+", MENU_ITEM_ACTION},
                 {"-", MENU_ITEM_ACTION},
                 {"Confirm", MENU_ITEM_BACK}}}
};

static const MenuPageDefinition *MenuData_FindPage(MenuIP ip)
{
    MenuIP path = (MenuIP)(ip & ~MENU_IP_CURSOR_MASK);
    uint8_t page_count = (uint8_t)(sizeof(MenuPages) / sizeof(MenuPages[0]));
    uint8_t page;

    for (page = 0; page < page_count; page++)
    {
        if (MenuPages[page].path == path)
        {
            return &MenuPages[page];
        }
    }

    return 0;
}

uint8_t MenuData_GetItemCount(MenuIP ip)
{
    const MenuPageDefinition *page = MenuData_FindPage(ip);
    return (page == 0) ? 0U : page->item_count;
}

const char *MenuData_GetItemLabel(MenuIP ip, uint8_t item)
{
    const MenuPageDefinition *page = MenuData_FindPage(ip);

    if ((page == 0) || (item == 0U) || (item > page->item_count))
    {
        return 0;
    }

    return page->items[item - 1U].label;
}

MenuItemType MenuData_GetCurrentItemType(MenuIP ip)
{
    const MenuPageDefinition *page = MenuData_FindPage(ip);
    uint8_t cursor;

    if (page == 0)
    {
        return MENU_ITEM_NONE;
    }

    cursor = MenuIP_GetCursor(ip);
    if ((cursor == 0U) || (cursor > page->item_count))
    {
        return MENU_ITEM_NONE;
    }

    return page->items[cursor - 1U].type;
}
