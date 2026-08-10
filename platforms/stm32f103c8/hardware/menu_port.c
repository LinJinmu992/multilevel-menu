#include "menu_port.h"
#include "OLED.h"

void MenuPort_InitDisplay(void) {}
void MenuPort_Clear(void) { OLED_Clear(); }
void MenuPort_ShowChar(uint8_t l, uint8_t c, char v) { OLED_ShowChar(l, c, v); }
void MenuPort_ShowString(uint8_t l, uint8_t c, const char *v) { OLED_ShowString(l, c, v); }
void MenuPort_ShowNum(uint8_t l, uint8_t c, uint32_t v, uint8_t n) { OLED_ShowNum(l, c, v, n); }
