#include "menu_port.h"
#include "main.h"
#include "OLED.h"

void MenuPort_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    gpio.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);

    gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    HAL_GPIO_Init(GPIOB, &gpio);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_4 | GPIO_PIN_6;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio);

    OLED_Init();
}

void MenuPort_Clear(void) { OLED_Clear(); }
void MenuPort_ShowChar(uint8_t l, uint8_t c, char v) { OLED_ShowChar(l, c, v); }
void MenuPort_ShowString(uint8_t l, uint8_t c, const char *v) { OLED_ShowString(l, c, (char *)v); }
void MenuPort_ShowNum(uint8_t l, uint8_t c, uint32_t v, uint8_t n) { OLED_ShowNum(l, c, v, n); }
bool MenuPort_IsConfirmPressed(void) { return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET; }
