#include "MenuIP.h"

/* Private function declarations ------------------------------------------- */

static MenuIP MenuIP_GetLevelMask(uint8_t level);

/* Public function implementations ----------------------------------------- */

uint8_t MenuIP_GetCursor(MenuIP ip)
{
	return (uint8_t)(ip & MENU_IP_CURSOR_MASK);
}

uint8_t MenuIP_GetItem(MenuIP ip, uint8_t level)
{
	MenuIP mask = MenuIP_GetLevelMask(level);
	if (mask == 0) return 0;
	return (uint8_t)((ip & mask) >> (level * 4));
}

uint8_t MenuIP_GetDepth(MenuIP ip)
{
	if (MenuIP_GetItem(ip, 3) != 0) return 3;
	if (MenuIP_GetItem(ip, 2) != 0) return 2;
	if (MenuIP_GetItem(ip, 1) != 0) return 1;
	return 0;
}

MenuIP MenuIP_MoveNext(MenuIP ip, uint8_t item_count)
{
	uint8_t cursor;
	if (item_count == 0) return ip;
	cursor = MenuIP_GetCursor(ip) + 1;
	if (cursor > item_count) cursor = 1;
	return (MenuIP)((ip & ~MENU_IP_CURSOR_MASK) | cursor);
}

MenuIP MenuIP_MovePrevious(MenuIP ip, uint8_t item_count)
{
	uint8_t cursor;
	if (item_count == 0) return ip;
	cursor = MenuIP_GetCursor(ip);
	cursor = (cursor <= 1) ? item_count : cursor - 1;
	return (MenuIP)((ip & ~MENU_IP_CURSOR_MASK) | cursor);
}

MenuIP MenuIP_Enter(MenuIP ip)
{
	uint8_t depth = MenuIP_GetDepth(ip);
	uint8_t cursor = MenuIP_GetCursor(ip);
	uint8_t next_level;

	if ((cursor == 0) || (depth >= 3)) return ip;
	next_level = depth + 1;
	ip &= ~MENU_IP_CURSOR_MASK;
	ip |= (MenuIP)((MenuIP)cursor << (next_level * 4));
	ip |= 0x0001;
	return ip;
}

MenuIP MenuIP_Back(MenuIP ip)
{
	uint8_t depth = MenuIP_GetDepth(ip);
	if (depth == 0) return MENU_IP_ROOT;
	return (MenuIP)(ip & ~MenuIP_GetLevelMask(depth));
}

MenuIP MenuIP_Make(uint8_t level1, uint8_t level2,
				   uint8_t level3, uint8_t cursor)
{
	return (MenuIP)(
		((MenuIP)(level1 & 0x0F) << 4) |
		((MenuIP)(level2 & 0x0F) << 8) |
		((MenuIP)(level3 & 0x0F) << 12) |
		(MenuIP)(cursor & 0x0F)
	);
}

/* Private function implementations ---------------------------------------- */

/* 根据层级取得对应的位掩码，仅供本文件内部调用 */
static MenuIP MenuIP_GetLevelMask(uint8_t level)
{
	switch (level)
	{
		case 1: return MENU_IP_LEVEL1_MASK;
		case 2: return MENU_IP_LEVEL2_MASK;
		case 3: return MENU_IP_LEVEL3_MASK;
		default: return 0;
	}
}
