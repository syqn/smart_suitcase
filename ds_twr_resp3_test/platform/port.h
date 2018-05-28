/*! ----------------------------------------------------------------------------
 * @file	port.h
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


#ifndef PORT_H_
#define PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "stm32f10x.h"/////////////////////////////////
#ifndef __IO
#define __IO    volatile                  /*!< defines 'read / write' permissions   */
#endif
#include "stdint.h"
#include "embARC.h"
#include "embARC_debug.h"
#include "deca_device_api.h"
#include "dev_common.h"
#include "deca_regs.h"
#include "LN298.h"

/*typedef struct _DWM1000_t {
	uint8_t spi_master;
	uint8_t spi_cs;
	uint32_t spi_freq;

	uint8_t gpio_int_busy;
	uint8_t pin_int_busy;
	DEV_GPIO_HANDLER gpio_int_handler;

	uint8_t gpio_rst;
	uint8_t pin_rst;

	uint8_t gpio_cs;
	uint8_t pin_cs;

	uint32_t last_cmd;
	uint32_t dwm1000_to_send;  flag of rw009 has data to send

} DWM1000_DEF, * DWM1000_DEF_PTR;*/

DEV_SPI_PTR DWM1000_port;
DEV_GPIO_PTR DWM1000_res;
DEV_GPIO_PTR DWM1000_IRQ;
DEV_GPIO_PTR DWM1000_CS;

//void USART_puts(uint8_t *s,uint8_t len);
	
extern int writetospi_serial(uint16_t headerLength,
                             const uint8_t *headerBuffer,
                             uint32_t bodylength,
                             const uint8_t *bodyBuffer);

extern int readfromspi_serial(uint16_t	headerLength,
                              const uint8_t *headerBuffer,
                              uint32_t readlength,
                              uint8_t *readBuffer );

#define writetospi  writetospi_serial
#define readfromspi readfromspi_serial

#define EMSK_DWM1000_RES_OFFSET		(24)
#define EMSK_DWM1000_RES_MASK		((0x01) << EMSK_DWM1000_RES_OFFSET)
//#define EMSK_DWM1000_IRQ_OFFSET		(16)
//#define EMSK_DWM1000_IRQ_MASK		((0x01) << EMSK_DWM1000_IRQ_OFFSET)
//#define EMSK_DWM1000_CS_OFFSET		(16)
//#define EMSK_DWM1000_CS_MASK		((0x01) << EMSK_DWM1000_CS_OFFSET)

#define lcd_display_str EMBARC_PRINTF
#define DWT_LEDS_ENABLE 1

#define GPIO_LED_LEN 		2
#define GPIO_PIN2_RXLED_8 	0x04
#define GPIO_PIN3_TXLED_8 	0x10
#define GPIO_LED_BYTE_NUM 	1
void dwt_setlnapamode(void);

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
decaIrqStatus_t port_GetEXT_IRQStatus(void);

int NVIC_DisableDECAIRQ(void);
int NVIC_Configuration(void);

//int is_IRQ_enabled(void);

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn peripherals_init()
 *
 * @brief Initialise all peripherals.
 *
 * @param none
 *
 * @return none
 */
void peripherals_init (void);

void SPI_ChangeRate(void *scalingfactor);
void SPI_ConfigFastRate(uint16_t scalingfactor);

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_low()
 *
 * @brief Set SPI rate to less than 3 MHz to properly perform DW1000 initialisation.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_low (void);

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_high()
 *
 * @brief Set SPI rate as close to 20 MHz as possible for optimum performances.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_high (void);

/**
 * @brief get current system time in millisecond
 * @return  millisecond
 */
uint32_t timer_read_ms(void);

void DWM1000_spi_init(void);
void DWM1000_gpio_open(void);
void DWM1000_IRQ_open(void);

void reset_DW1000(void);
void setup_DW1000RSTnIRQ(int enable);

int ETH_GPIOConfigure(void);

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */
