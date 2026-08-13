#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>

/**
 * @brief 使用 SysTick 进行阻塞式微秒延时。
 * @param us 延时时间，单位为微秒。
 */
void Delay_us(uint32_t us);

/**
 * @brief 使用 SysTick 进行阻塞式毫秒延时。
 * @param ms 延时时间，单位为毫秒。
 */
void Delay_ms(uint32_t ms);

/**
 * @brief 使用 SysTick 进行阻塞式秒级延时。
 * @param s 延时时间，单位为秒。
 */
void Delay_s(uint32_t s);

#endif
