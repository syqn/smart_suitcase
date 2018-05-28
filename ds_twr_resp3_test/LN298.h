/*
 * LN298.h
 *
 *  Created on: 2018Äê5ÔÂ25ÈÕ
 *      Author: dj201
 */

#ifndef LN298_H_
#define LN298_H_

#include "embARC.h"
#include "embARC_debug.h"
#include <stdlib.h>
#include "board/emsk/drivers/mux/mux.h"

#define EMSK_GPIO_CHECK_EXP_NORTN(EXPR)		CHECK_EXP_NOERCD(EXPR, error_exit)

#define EMSK_LN298_OFFSET		(16)
#define EMSK_LN298_MASK		((0xff) << EMSK_LN298_OFFSET)

#define test_offset  (1)
#define test_mask    (0x01<<test_offset)
#define test_dir     (0x01<<test_offset)

DEV_GPIO_PTR LN298_port;
DEV_GPIO_PTR test;
DEV_GPIO_BIT_ISR test_isr;

void gpio_init(void);
void LN298_init(void);
void LN298_forward(void);
void LN298_left(void);
void LN298_right(void);
void LN298_stop(void);
void LN298_back(void);






#endif /* LN298_H_ */
