#include "LN298.h"
#include "emsk/emsk.h"

int LN298_flag = 50;

static void test_int_isr(void *ptr)
{
	if(LN298_flag==4){
		LN298_flag=0;
	}
	else{
		LN298_flag++;
	}
}

void gpio_init(void)
{
    DEV_GPIO_INT_CFG test_int;
	test=gpio_get_dev(DEV_GPIO_PORT_A);
    test_isr.int_bit_ofs=test_offset;
    test_isr.int_bit_handler=test_int_isr;
	test_int.int_bit_debounce = GPIO_INT_BIT_ENA_DEBOUNCE(test_offset);
	test_int.int_bit_mask = test_mask;
	test_int.int_bit_polarity = GPIO_INT_BIT_POL_FALL_EDGE(test_offset);
	test_int.int_bit_type = GPIO_INT_BIT_EDGE_TRIG(test_offset);
	test->gpio_open((uint32_t)(1<<test_offset));
	test->gpio_control(GPIO_CMD_SET_BIT_DIR_INPUT,(void *)test_mask);
	test->gpio_control(GPIO_CMD_SET_BIT_INT_CFG,(void *)&test_int);
	test->gpio_control(GPIO_CMD_SET_BIT_ISR,(void *)&test_isr);
	test->gpio_control(GPIO_CMD_ENA_BIT_INT,(void *)test_mask);
}

void LN298_init(void)
{
	LN298_port = gpio_get_dev(DEV_GPIO_PORT_C);
	LN298_port->gpio_open(DEV_GPIO_PORT_C);
	LN298_port->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(EMSK_LN298_MASK));
	LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
}

void LN298_stop(void)
{
	while(LN298_flag--)
	{
		LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
	}
}

void LN298_forward(void)
{
	while(LN298_flag--)
	{
		LN298_port->gpio_write(0x55 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(10,OSP_DELAY_OS_COMPAT_DISABLE);
		LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(10,OSP_DELAY_OS_COMPAT_DISABLE);
	}
}

void LN298_left(void)
{
	while(LN298_flag--)
	{
		LN298_port->gpio_write(0x66 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(5,OSP_DELAY_OS_COMPAT_DISABLE);
		LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(15,OSP_DELAY_OS_COMPAT_DISABLE);
	}
}

void LN298_right(void)
{
	while(LN298_flag--)
	{
		LN298_port->gpio_write(0x99 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(5,OSP_DELAY_OS_COMPAT_DISABLE);
		LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(15,OSP_DELAY_OS_COMPAT_DISABLE);
	}
}

void LN298_back(void)
{
	while(LN298_flag--)
	{
		LN298_port->gpio_write(0xaa << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(10,OSP_DELAY_OS_COMPAT_DISABLE);
		LN298_port->gpio_write(0x00 << EMSK_LN298_OFFSET,(uint32_t)EMSK_LN298_MASK);
		board_delay_ms(10,OSP_DELAY_OS_COMPAT_DISABLE);
	}
}
