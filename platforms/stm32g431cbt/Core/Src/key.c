#include "key.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

/* Private macros ----------------------------------------------------------- */

/* 新电平连续出现指定次数后，才确认按键状态发生变化。 */
#define KEY_DEBOUNCE_SAMPLES 2U

/* Private types ------------------------------------------------------------ */

typedef struct
{
    /* 已通过消抖确认的按键状态。 */
    GPIO_PinState stable_state;

    /* 最近连续采样到、等待确认的候选状态。 */
    GPIO_PinState candidate_state;

    /* 候选状态连续出现的次数。 */
    uint8_t candidate_count;
} KeyState;

/* Private variables -------------------------------------------------------- */

static KeyState confirm_key;
static KeyState next_key;
static KeyState previous_key;

/* Private function declarations ------------------------------------------- */

static void KeyState_Init(KeyState *key, GPIO_PinState state);
static bool KeyState_Update(KeyState *key, GPIO_PinState sample);

/* Public function implementations ----------------------------------------- */

void Key_Init(void)
{
    /*
     * 将上电时读取到的实际电平作为初始稳定状态。
     * 这样即使上电时按键正被按住，也不会被误判为一次新的按下事件。
     */
    KeyState_Init(&confirm_key,
                  HAL_GPIO_ReadPin(KEY_CONFIRM_GPIO_Port, KEY_CONFIRM_Pin));
    KeyState_Init(&next_key,
                  HAL_GPIO_ReadPin(KEY_NEXT_GPIO_Port, KEY_NEXT_Pin));
    KeyState_Init(&previous_key,
                  HAL_GPIO_ReadPin(KEY_PREVIOUS_GPIO_Port, KEY_PREVIOUS_Pin));
}

MenuEvent Key_Scan(void)
{
    bool next_pressed;
    bool previous_pressed;
    bool confirm_pressed;

    next_pressed = KeyState_Update(
        &next_key,
        HAL_GPIO_ReadPin(KEY_NEXT_GPIO_Port, KEY_NEXT_Pin));
    previous_pressed = KeyState_Update(
        &previous_key,
        HAL_GPIO_ReadPin(KEY_PREVIOUS_GPIO_Port, KEY_PREVIOUS_Pin));
    confirm_pressed = KeyState_Update(
        &confirm_key,
        HAL_GPIO_ReadPin(KEY_CONFIRM_GPIO_Port, KEY_CONFIRM_Pin));

    /* 每轮最多返回一个事件，优先级为 NEXT > PREVIOUS > CONFIRM。 */
    if (next_pressed)
    {
        return MENU_EVENT_NEXT;
    }
    if (previous_pressed)
    {
        return MENU_EVENT_PREVIOUS;
    }
    if (confirm_pressed)
    {
        return MENU_EVENT_CONFIRM;
    }

    return MENU_EVENT_NONE;
}

/* Private function implementations ---------------------------------------- */

static void KeyState_Init(KeyState *key, GPIO_PinState state)
{
    key->stable_state = state;
    key->candidate_state = state;

    /* 初始电平直接视为已经稳定，无需等待后续采样确认。 */
    key->candidate_count = KEY_DEBOUNCE_SAMPLES;
}

static bool KeyState_Update(KeyState *key, GPIO_PinState sample)
{
    GPIO_PinState previous_state;

    /* 电平刚发生变化：记录新候选状态，并重新开始消抖计数。 */
    if (sample != key->candidate_state)
    {
        key->candidate_state = sample;
        key->candidate_count = 1U;
        return false;
    }

    /* 候选状态保持不变：累计连续采样次数，计数达到阈值后停止。 */
    if (key->candidate_count < KEY_DEBOUNCE_SAMPLES)
    {
        key->candidate_count++;
    }

    /*
     * 连续次数不足时不能确认新状态；候选状态与稳定状态相同时，
     * 说明按键没有发生新的状态转换，也不需要重复处理。
     */
    if ((key->candidate_count < KEY_DEBOUNCE_SAMPLES) ||
        (key->stable_state == key->candidate_state))
    {
        return false;
    }

    previous_state = key->stable_state;
    key->stable_state = key->candidate_state;

    /* 按键低电平有效，只在“松开(SET) -> 按下(RESET)”时报告事件。 */
    return (previous_state == GPIO_PIN_SET) &&
           (key->stable_state == GPIO_PIN_RESET);
}
