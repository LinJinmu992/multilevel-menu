#include "MenuData.h"

#define MENU_PAGE_MAX_ITEMS 4

typedef struct
{
	MenuIP path;                         /* 页面路径，不包含光标 */
	uint8_t item_count;                  /* 页面实际菜单项数量 */
	MenuItemType items[MENU_PAGE_MAX_ITEMS];
} MenuPageInfo;

/*
 * IP只记录当前位置；这张表说明每个页面有几项，以及每项按确认后的行为。
 * 页面路径必须将最低4位（光标位）置0。
 */
static const MenuPageInfo MenuPages[] =
{
	/* 主菜单：adc、error、pid、Ciallo! */
	{0x0000, 4, {MENU_ITEM_SUBMENU, MENU_ITEM_SUBMENU,
	             MENU_ITEM_SUBMENU, MENU_ITEM_ACTION}},

	/* adc菜单：三个功能项和exit */
	{0x0010, 4, {MENU_ITEM_ACTION, MENU_ITEM_ACTION,
	             MENU_ITEM_ACTION, MENU_ITEM_BACK}},

	/* error菜单：三个功能项和exit */
	{0x0020, 4, {MENU_ITEM_ACTION, MENU_ITEM_ACTION,
	             MENU_ITEM_ACTION, MENU_ITEM_BACK}},

	/* PID菜单：P、I、D参数和exit */
	{0x0030, 4, {MENU_ITEM_VALUE, MENU_ITEM_VALUE,
	             MENU_ITEM_VALUE, MENU_ITEM_BACK}},

	/* P、I、D编辑页面：数值、加、减、确认返回 */
	{0x0130, 4, {MENU_ITEM_ACTION, MENU_ITEM_ACTION,
	             MENU_ITEM_ACTION, MENU_ITEM_BACK}},
	{0x0230, 4, {MENU_ITEM_ACTION, MENU_ITEM_ACTION,
	             MENU_ITEM_ACTION, MENU_ITEM_BACK}},
	{0x0330, 4, {MENU_ITEM_ACTION, MENU_ITEM_ACTION,
	             MENU_ITEM_ACTION, MENU_ITEM_BACK}}
};

static const MenuPageInfo *MenuData_FindPage(MenuIP ip)
{
	MenuIP path;
	uint8_t i;
	uint8_t page_count;

	path = (MenuIP)(ip & ~MENU_IP_CURSOR_MASK);
	page_count = (uint8_t)(sizeof(MenuPages) / sizeof(MenuPages[0]));

	for (i = 0; i < page_count; i++)
	{
		if (MenuPages[i].path == path)
		{
			return &MenuPages[i];
		}
	}

	return 0;
}

uint8_t MenuData_GetItemCount(MenuIP ip)
{
	const MenuPageInfo *page;

	page = MenuData_FindPage(ip);
	if (page == 0)
	{
		return 0;
	}

	return page->item_count;
}

MenuItemType MenuData_GetCurrentItemType(MenuIP ip)
{
	const MenuPageInfo *page;
	uint8_t cursor;

	page = MenuData_FindPage(ip);
	if (page == 0)
	{
		return MENU_ITEM_NONE;
	}

	cursor = MenuIP_GetCursor(ip);
	if ((cursor == 0) || (cursor > page->item_count))
	{
		return MENU_ITEM_NONE;
	}

	return page->items[cursor - 1];
}
