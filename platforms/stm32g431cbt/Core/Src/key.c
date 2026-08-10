#include "key.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

#define KEY_DEBOUNCE_SAMPLES 2U

typedef struct
{
    GPIO_PinState stable_state;
    GPIO_PinState candidate_state;
    uint8_t candidate_count;
} KeyState;

static KeyState confirm_key;
static KeyState next_key;
static KeyState previous_key;

static void KeyState_Init(KeyState *key, GPIO_PinState state)
{
    key->stable_state = state;
    key->candidate_state = state;
    key->candidate_count = KEY_DEBOUNCE_SAMPLES;
}

static bool KeyState_Update(KeyState *key, GPIO_PinState sample)
{
    GPIO_PinState previous_state;

    if (sample != key->candidate_state)
    {
        key->candidate_state = sample;
        key->candidate_count = 1U;
        return false;
    }

    if (key->candidate_count < KEY_DEBOUNCE_SAMPLES)
    {
        key->candidate_count++;
    }

    if ((key->candidate_count < KEY_DEBOUNCE_SAMPLES) ||
        (key->stable_state == key->candidate_state))
    {
        return false;
    }

    previous_state = key->stable_state;
    key->stable_state = key->candidate_state;

    return (previous_state == GPIO_PIN_SET) &&
           (key->stable_state == GPIO_PIN_RESET);
}

void Key_Init(void)
{
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
