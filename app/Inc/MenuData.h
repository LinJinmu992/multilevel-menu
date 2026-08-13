#ifndef __MENU_DATA_H
#define __MENU_DATA_H

#include "MenuIP.h"

typedef enum
{
    MENU_ITEM_NONE = 0, /**< 无效或不存在的菜单项。 */
    MENU_ITEM_SUBMENU, /**< 确认后进入普通子菜单。 */
    MENU_ITEM_ACTION, /**< 确认后执行功能动作。 */
    MENU_ITEM_VALUE, /**< 确认后进入参数编辑页面。 */
    MENU_ITEM_BACK /**< 确认后返回上一级菜单。 */
} MenuItemType;

/**
 * @brief 获取指定菜单页面包含的菜单项数量。
 * @param ip 包含页面路径和光标位置的菜单 IP。
 * @return 页面项目数；页面不存在时返回 0。
 */
uint8_t MenuData_GetItemCount(MenuIP ip);

/**
 * @brief 获取指定菜单项的显示文字。
 * @param ip 包含页面路径和光标位置的菜单 IP。
 * @param item 从 1 开始计数的菜单项编号。
 * @return 指向只读、以 '\0' 结尾字符串的指针；参数无效时返回空指针。
 */
const char *MenuData_GetItemLabel(MenuIP ip, uint8_t item);

/**
 * @brief 获取当前光标所指菜单项的行为类型。
 * @param ip 包含页面路径和光标位置的菜单 IP。
 * @return 当前项目类型；页面或光标无效时返回 MENU_ITEM_NONE。
 */
MenuItemType MenuData_GetCurrentItemType(MenuIP ip);

#endif
