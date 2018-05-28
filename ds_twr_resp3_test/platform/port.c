/*! ----------------------------------------------------------------------------
 * @file	port.c
 * @brief	HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */
#include "deca_sleep.h"
//#include "lcd.h"
#include "port.h"

//设置读写指示灯模式为模式3，即读写灯都亮
void dwt_setlnapamode(void)
{
	uint8 buf[GPIO_MODE_LEN];

	// Set the GPIO to control external PA/LNA
	dwt_readfromdevice(GPIO_CTRL_ID, GPIO_MODE_OFFSET, GPIO_LED_LEN, buf);

	buf[GPIO_LED_BYTE_NUM] |= (GPIO_PIN2_RXLED_8 + GPIO_PIN3_TXLED_8);

	dwt_writetodevice(GPIO_CTRL_ID, GPIO_MODE_OFFSET, GPIO_LED_LEN, buf);
}

//暂时不用
decaIrqStatus_t port_GetEXT_IRQStatus(void)
{
	ITStatus bitstatus = RESET;
	uint32_t enablestatus = 0;
//	/* Check the parameters */
//	assert_param(IS_GET_EXTI_LINE(EXTI_Line));
//
//	enablestatus =  EXTI->IMR & EXTI_Line;
	EMBARC_PRINTF("\r\n The port_GetEXT_IRQStatus is used. \r\n");
	if (enablestatus != (uint32_t)RESET)
	{
	bitstatus = SET;
	}
	else
	{
	bitstatus = RESET;
	}
	return bitstatus;
}

int No_Configuration(void)
{
	return -1;
}

//设置SPI频率
void SPI_ChangeRate(void *scalingfactor)
{
	DWM1000_port->spi_control(SPI_CMD_MST_SET_FREQ, scalingfactor);
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_low()
 *
 * @brief Set SPI rate to less than 3 MHz to properly perform DW1000 initialisation.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_low (void)
{
	uint32_t rate_low = 2500000U;
    SPI_ChangeRate(CONV2VOID(rate_low));
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_high()
 *
 * @brief Set SPI rate as close to 20 MHz as possible for optimum performances.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_high (void)
{
//	uint32_t rate_high = 6260000U;
	uint32_t rate_high = 1000000U;//只发送，最大6.25MHz；既发送又接收，最大5MHz，但实测1MHz最稳定
    SPI_ChangeRate(CONV2VOID(rate_high));
}

/**
 * @brief get current system time in millisecond
 * @return  millisecond
 */
uint32_t timer_read_ms(void)
{
	return OSP_GET_CUR_MS();
}

void DWM1000_spi_init(void)
{
	uint32_t DWM1000_status;
	uint32_t DWM1000_DFS = 8;

	DWM1000_port = spi_get_dev(DW_SPI_0_ID);
	if (DWM1000_port->spi_open(DWM1000_port->spi_info.mode, DWM1000_port->spi_info.freq) == E_OK) {
		DWM1000_port->spi_control(SPI_CMD_MST_SET_FREQ, CONV2VOID(2000000U));
		DWM1000_port->spi_control(SPI_CMD_SET_CLK_MODE, CONV2VOID(SPI_CLK_MODE_3));
		DWM1000_port->spi_control(SPI_CMD_ENA_DEV, CONV2VOID(NULL));
		DWM1000_port->spi_control(SPI_CMD_MST_SEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
	}
}

void DWM1000_gpio_open(void)
{
	DWM1000_res = gpio_get_dev(DEV_GPIO_PORT_A);
	//EMSK_GPIO_CHECK_EXP_NORTN(LN298_port != NULL);
	if (DWM1000_res->gpio_open(DEV_GPIO_PORT_A) == E_OPNED) {
		DWM1000_res->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(EMSK_DWM1000_RES_MASK));
	}

	led_write(0x0001, BOARD_LED_MASK);
//error_exit:
//	return;
}

//复位
void reset_DW1000(void)
{
	uint32_t pmod5_A24 = 0;

	DWM1000_res->gpio_write(pmod5_A24 << EMSK_DWM1000_RES_OFFSET,(uint32_t)EMSK_DWM1000_RES_MASK);
	deca_sleep(5);//正常值是3ms
	DWM1000_res->gpio_write(~pmod5_A24 << EMSK_DWM1000_RES_OFFSET,(uint32_t)EMSK_DWM1000_RES_MASK);
    deca_sleep(5);
}

/*
! ------------------------------------------------------------------------------------------------------------------
 * @fn peripherals_init()
 *
 * @brief Initialise all peripherals.
 *
 * @param none
 *
 * @return none*/

void peripherals_init (void)
{
	board_init();
//	gpio_init();
	LN298_init();
	io_pmod_config(PMOD_4,PMOD_GPIO,0);
	io_pmod_config(PMOD_5,PMOD_GPIO,0);
	DWM1000_gpio_open();
	DWM1000_spi_init();
}


