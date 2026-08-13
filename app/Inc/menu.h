#ifndef __MENU_H
#define __MENU_H

#include <stdint.h>

typedef enum
{
    MENU_EVENT_NONE = 0, /**< 没有新的按键事件。 */
    MENU_EVENT_NEXT, /**< 将光标移动到下一菜单项。 */
    MENU_EVENT_PREVIOUS, /**< 将光标移动到上一菜单项。 */
    MENU_EVENT_CONFIRM /**< 确认当前菜单项。 */
} MenuEvent;

/** @brief 按当前菜单状态刷新整个菜单画面。 */
void MenuDisplay(void);

/**
 * @brief 处理一个菜单输入事件并在状态变化后刷新画面。
 * @param event 由按键层产生的菜单事件；MENU_EVENT_NONE 不执行操作。
 */
void Menu_HandleEvent(MenuEvent event);

#endif
