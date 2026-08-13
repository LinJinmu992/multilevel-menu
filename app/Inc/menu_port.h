#ifndef MENU_PORT_H
#define MENU_PORT_H

#include <stdint.h>

/** @brief 初始化当前平台使用的菜单显示设备；在首次绘制前调用一次。 */
void MenuPort_InitDisplay(void);

/** @brief 清除菜单显示区域。 */
void MenuPort_Clear(void);

/**
 * @brief 在指定字符位置显示一个字符。
 * @param line 从 1 开始计数的显示行。
 * @param column 从 1 开始计数的字符列。
 * @param value 要显示的字符。
 */
void MenuPort_ShowChar(uint8_t line, uint8_t column, char value);

/**
 * @brief 从指定字符位置开始显示字符串。
 * @param line 从 1 开始计数的显示行。
 * @param column 从 1 开始计数的起始字符列。
 * @param value 指向只读、以 '\0' 结尾字符串的非空指针。
 */
void MenuPort_ShowString(uint8_t line, uint8_t column, const char *value);

/**
 * @brief 以十进制无符号格式显示固定长度数值。
 * @param line 从 1 开始计数的显示行。
 * @param column 从 1 开始计数的起始字符列。
 * @param value 要显示的无符号数值。
 * @param length 要显示的十进制位数。
 */
void MenuPort_ShowNum(uint8_t line, uint8_t column, uint32_t value, uint8_t length);

#endif
