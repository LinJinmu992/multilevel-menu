#ifndef __MENU_DATA_H
#define __MENU_DATA_H

#include "MenuIP.h"

/* 菜单项按下确认键后应执行的操作类型 */
typedef enum
{
	MENU_ITEM_NONE = 0,
	MENU_ITEM_SUBMENU,   /* 进入普通子菜单 */
	MENU_ITEM_ACTION,    /* 执行功能，IP保持不变 */
	MENU_ITEM_VALUE,     /* 进入参数编辑页面 */
	MENU_ITEM_BACK       /* 返回上一级 */
} MenuItemType;

/* 获取当前页面实际包含的菜单项数量 */
uint8_t MenuData_GetItemCount(MenuIP ip);

/* 获取当前光标所指菜单项的操作类型 */
MenuItemType MenuData_GetCurrentItemType(MenuIP ip);

#endif
