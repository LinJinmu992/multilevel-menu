#include "MenuData.h"

/* 当前OLED每页最多显示4个菜单项 */
#define MENU_PAGE_MAX_ITEMS 4

/* 描述一个菜单页面，而不是保存当前运行状态 */
typedef struct
{
	MenuIP path;                         /* 页面路径，不包含光标 */
	uint8_t item_count;                  /* 页面实际菜单项数量 */
	MenuItemType items[MENU_PAGE_MAX_ITEMS]; /* 从第1行到第4行的菜单项类型 */
} MenuPageInfo;

/*
 * 菜单说明表，描述每个页面的菜单项数量和每项按确认后的行为。
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

/*
 * 函数作用：根据当前菜单IP，在MenuPages菜单表中查找对应的页面信息。
 *
 * 输入：包含菜单路径和光标位置的完整IP，例如0x0032。
 * 处理：先清除最低4位光标，将0x0032转换成页面路径0x0030，
 *       再遍历MenuPages数组并比较每个页面的path。
 * 返回：找到时返回对应MenuPageInfo结构体在数组中的地址；
 *       找不到时返回空指针0。
 */
static const MenuPageInfo *MenuData_FindPage(MenuIP ip)
{
	MenuIP path;
	uint8_t i;
	uint8_t page_count;

	/* 清除最低4位光标，例如0x0032会转换成PID页面路径0x0030 */
	path = (MenuIP)(ip & ~MENU_IP_CURSOR_MASK);

	/* 整个数组字节数除以单个元素字节数，得到页面数量 */
	page_count = (uint8_t)(sizeof(MenuPages) / sizeof(MenuPages[0]));

	/* 逐个比较页面路径 */
	for (i = 0; i < page_count; i++)
	{
		if (MenuPages[i].path == path)
		{
			/* &表示取地址，返回当前结构体元素在数组中的地址 */
			return &MenuPages[i];
		}
	}

	/* 0作为空指针，表示没有找到页面 */
	return 0;
}

/*
 * 函数作用：获取当前IP所对应页面的菜单项总数，供光标循环移动使用。
 * 输入：包含菜单路径和光标位置的完整IP。
 * 返回：找到页面时返回该页面的item_count；找不到页面时返回0。
 */
uint8_t MenuData_GetItemCount(MenuIP ip)
{
	/* page是指向只读MenuPageInfo结构体的指针 */
	const MenuPageInfo *page;

	page = MenuData_FindPage(ip);
	/* 使用指针前先判断是否为空，避免访问无效地址 */
	if (page == 0)
	{
		return 0;
	}

	/* 指向结构体的指针使用->访问成员 */
	return page->item_count;
}

/*
 * 函数作用：获取当前光标所指菜单项的类型，供确认键判断进入、执行或返回。
 * 输入：包含菜单路径和光标位置的完整IP。
 * 返回：当前菜单项对应的MenuItemType；页面或光标无效时返回MENU_ITEM_NONE。
 */
MenuItemType MenuData_GetCurrentItemType(MenuIP ip)
{
	const MenuPageInfo *page;
	uint8_t cursor;

	page = MenuData_FindPage(ip);
	if (page == 0)
	{
		return MENU_ITEM_NONE;
	}

	/* IP中的光标从1开始计数 */
	cursor = MenuIP_GetCursor(ip);
	if ((cursor == 0) || (cursor > page->item_count))
	{
		return MENU_ITEM_NONE;
	}

	/* C数组下标从0开始，因此光标位置需要减1 */
	return page->items[cursor - 1];
}
