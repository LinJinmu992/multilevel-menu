#ifndef __MENU_H
#define __MENU_H

#include <stdint.h>

typedef enum
{
    MENU_EVENT_NONE = 0,
    MENU_EVENT_NEXT,
    MENU_EVENT_PREVIOUS,
    MENU_EVENT_CONFIRM
} MenuEvent;

void MenuDisplay(void);
void Menu_HandleEvent(MenuEvent event);

#endif
