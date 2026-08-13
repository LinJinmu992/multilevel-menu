#ifndef __MENU_IP_H
#define __MENU_IP_H

#include <stdint.h>

/** @brief 以三个 4 位页面编号和一个 4 位光标编号编码菜单位置。 */
typedef uint16_t MenuIP;

/* IP的四个十六进制位：三级菜单、二级菜单、一级菜单、光标位置 */
#define MENU_IP_CURSOR_MASK	((MenuIP)0x000F)
#define MENU_IP_LEVEL1_MASK	((MenuIP)0x00F0)
#define MENU_IP_LEVEL2_MASK	((MenuIP)0x0F00)
#define MENU_IP_LEVEL3_MASK	((MenuIP)0xF000)
#define MENU_IP_ROOT		((MenuIP)0x0001)

/**
  * @brief  获取IP最右边一位保存的光标位置
  * @param  ip 菜单IP
  * @retval 光标位置，通常为1~4
  */
uint8_t MenuIP_GetCursor(MenuIP ip);

/**
  * @brief  获取IP中指定层级的菜单编号
  * @param  ip 菜单IP
  * @param  level 菜单层级，取值为1、2或3
  * @retval 对应层级的菜单编号；层级无效时返回0
  */
uint8_t MenuIP_GetItem(MenuIP ip, uint8_t level);

/**
  * @brief  判断当前IP所在的菜单深度
  * @param  ip 菜单IP
  * @retval 0表示主菜单，1~3表示当前所在的菜单层级
  */
uint8_t MenuIP_GetDepth(MenuIP ip);

/**
  * @brief  光标向下一项移动，越过最后一项时回到第一项
  * @param  ip 当前菜单IP
  * @param  item_count 当前页面的菜单项总数
  * @retval 移动光标后的新IP；item_count为0时返回原IP
  */
MenuIP MenuIP_MoveNext(MenuIP ip, uint8_t item_count);

/**
  * @brief  光标向上一项移动，在第一项继续上移时跳到最后一项
  * @param  ip 当前菜单IP
  * @param  item_count 当前页面的菜单项总数
  * @retval 移动光标后的新IP；item_count为0时返回原IP
  */
MenuIP MenuIP_MovePrevious(MenuIP ip, uint8_t item_count);

/**
  * @brief  进入下一级菜单，把当前光标位置写入下一级并将光标重置为1
  * @param  ip 当前菜单IP
  * @retval 进入下一级后的新IP；已经到第三级或光标为0时返回原IP
  */
MenuIP MenuIP_Enter(MenuIP ip);

/**
  * @brief  返回上一级菜单，清除当前最深一级的菜单编号
  * @param  ip 当前菜单IP
  * @retval 返回上一级后的新IP；在主菜单时返回MENU_IP_ROOT
  */
MenuIP MenuIP_Back(MenuIP ip);

/**
  * @brief  根据三级菜单编号和光标位置组合出一个完整IP
  * @param  level1 一级菜单编号
  * @param  level2 二级菜单编号
  * @param  level3 三级菜单编号
  * @param  cursor 光标位置
  * @retval 组合后的16位菜单IP，每个参数只保留低4位
  */
MenuIP MenuIP_Make(uint8_t level1, uint8_t level2,
				   uint8_t level3, uint8_t cursor);

#endif
