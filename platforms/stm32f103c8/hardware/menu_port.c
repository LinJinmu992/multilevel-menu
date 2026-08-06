#include "menu_port.h"
#include "OLED.h"
#include "stm32f10x.h"

void MenuPort_Clear(void) { OLED_Clear(); }
void MenuPort_ShowChar(uint8_t l, uint8_t c, char v) { OLED_ShowChar(l, c, v); }
void MenuPort_ShowString(uint8_t l, uint8_t c, const char *v) { OLED_ShowString(l, c, (char *)v); }
void MenuPort_ShowNum(uint8_t l, uint8_t c, uint32_t v, uint8_t n) { OLED_ShowNum(l, c, v, n); }
bool MenuPort_IsConfirmPressed(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0; }
