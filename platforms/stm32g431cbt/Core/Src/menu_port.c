#include "menu_port.h"

/* Hardware pins are intentionally left unbound until the G431 board pinout is configured. */
void MenuPort_Clear(void) {}
void MenuPort_ShowChar(uint8_t l, uint8_t c, char v) { (void)l; (void)c; (void)v; }
void MenuPort_ShowString(uint8_t l, uint8_t c, const char *v) { (void)l; (void)c; (void)v; }
void MenuPort_ShowNum(uint8_t l, uint8_t c, uint32_t v, uint8_t n) { (void)l; (void)c; (void)v; (void)n; }
bool MenuPort_IsConfirmPressed(void) { return false; }
