#ifndef MENU_PORT_H
#define MENU_PORT_H

#include <stdint.h>

void MenuPort_InitDisplay(void);
void MenuPort_Clear(void);
void MenuPort_ShowChar(uint8_t line, uint8_t column, char value);
void MenuPort_ShowString(uint8_t line, uint8_t column, const char *value);
void MenuPort_ShowNum(uint8_t line, uint8_t column, uint32_t value, uint8_t length);

#endif
