#ifndef __LED_H
#define __LED_H

/** @brief 初始化两个低电平点亮的 LED GPIO，并默认关闭 LED。 */
void LED_Init(void);

/** @brief 点亮 LED1。 */
void LED1_ON(void);

/** @brief 熄灭 LED1。 */
void LED1_OFF(void);

/** @brief 点亮 LED2。 */
void LED2_ON(void);

/** @brief 熄灭 LED2。 */
void LED2_OFF(void);

/** @brief 翻转 LED1 当前亮灭状态。 */
void LED1_Turn(void);

/** @brief 翻转 LED2 当前亮灭状态。 */
void LED2_Turn(void);

#endif
