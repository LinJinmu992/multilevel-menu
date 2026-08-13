#ifndef __KEY_H
#define __KEY_H

#include <stdint.h>

/** @brief 将 PB1 和 PB11 配置为上拉输入按键。 */
void KEY_Init(void);

/**
 * @brief 阻塞消抖并读取一次按键释放事件。
 * @return 0 表示无按键，1 表示 PB1，2 表示 PB11。
 */
uint8_t Key_GetNum(void);


#endif
