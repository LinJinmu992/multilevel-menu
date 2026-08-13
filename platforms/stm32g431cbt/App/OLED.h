#ifndef __OLED_H
#define __OLED_H
#include <stdint.h>

/** @brief 初始化 OLED GPIO、控制器和显示缓冲区；使用显示接口前调用一次。 */
void OLED_Init(void);

/** @brief 清空整个 OLED 显示区域。 */
void OLED_Clear(void);

/**
 * @brief 在指定字符位置显示一个字符。
 * @param Line 从 1 开始计数的行号，范围为 1~4。
 * @param Column 从 1 开始计数的字符列，范围为 1~16。
 * @param Char 要显示的 ASCII 字符。
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

/**
 * @brief 从指定位置开始显示字符串。
 * @param Line 从 1 开始计数的行号，范围为 1~4。
 * @param Column 从 1 开始计数的起始字符列，范围为 1~16。
 * @param String 指向只读、以 '\0' 结尾字符串的非空指针。
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, const char *String);

/**
 * @brief 显示指定长度的十进制无符号数。
 * @param Line 从 1 开始计数的行号。
 * @param Column 从 1 开始计数的起始字符列。
 * @param Number 要显示的数值。
 * @param Length 要显示的十进制位数。
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
 * @brief 显示带正负号的十进制数。
 * @param Line 从 1 开始计数的行号。
 * @param Column 从 1 开始计数的符号起始列。
 * @param Number 要显示的有符号数值。
 * @param Length 不含符号位的十进制位数。
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
 * @brief 显示指定长度的十六进制数。
 * @param Line 从 1 开始计数的行号。
 * @param Column 从 1 开始计数的起始字符列。
 * @param Number 要显示的数值。
 * @param Length 要显示的十六进制位数。
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
 * @brief 显示指定长度的二进制数。
 * @param Line 从 1 开始计数的行号。
 * @param Column 从 1 开始计数的起始字符列。
 * @param Number 要显示的数值。
 * @param Length 要显示的二进制位数。
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
