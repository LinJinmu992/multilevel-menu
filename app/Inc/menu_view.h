#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <stdint.h>
#include "MenuIP.h"

/**
 * @brief 根据菜单位置和 PID 参数值绘制完整菜单画面。
 * @param ip 当前菜单页面路径和光标位置。
 * @param p 当前 P 参数显示值。
 * @param i 当前 I 参数显示值。
 * @param d 当前 D 参数显示值。
 */
void MenuView_Render(MenuIP ip, uint16_t p, uint16_t i, uint16_t d);

#endif
