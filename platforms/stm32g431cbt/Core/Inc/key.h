#ifndef KEY_H
#define KEY_H

#include "menu.h"

/** @brief 读取三个按键的上电电平并初始化消抖状态；进入主循环前调用一次。 */
void Key_Init(void);

/**
 * @brief 采样并消抖按键，返回本轮优先级最高的新按下事件。
 * @return 检测到的菜单事件；没有新按下事件时返回 MENU_EVENT_NONE。
 */
MenuEvent Key_Scan(void);

#endif
