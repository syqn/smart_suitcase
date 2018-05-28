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


//#define rcc_init(x)					RCC_Configuration(x)
//#define systick_init(x)				SysTick_Configuration(x)
//#define rtc_init(x)					RTC_Configuration(x)
//#define interrupt_init(x)			NVIC_Configuration(x)
//#define usart_init(x)				USART_Configuration(x)
//#define spi_init(x)					SPI_Configuration(x)
//#define gpio_init(x)				GPIO_Configuration(x)
//#define ethernet_init(x)			No_Configuration(x)
//#define fs_init(x)					No_Configuration(x)
//#define usb_init(x)					No_Configuration(x)

void dwt_setlnapamode(void)
{
	uint8 buf[GPIO_MODE_LEN];

	// Set the GPIO to control external PA/LNA
	dwt_readfromdevice(GPIO_CTRL_ID, GPIO_MODE_OFFSET, GPIO_LED_LEN, buf);

	buf[GPIO_LED_BYTE_NUM] |= (GPIO_PIN2_RXLED_8 + GPIO_PIN3_TXLED_8);

	dwt_writetodevice(GPIO_CTRL_ID, GPIO_MODE_OFFSET, GPIO_LED_LEN, buf);
}

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

//中断失能，要改的！！！！！！！！！！！！！！！！！
int NVIC_DisableDECAIRQ(void)
{
	/*EXTI_InitTypeDef EXTI_InitStructure;

	 Configure EXTI line
	EXTI_InitStructure.EXTI_Line = DECAIRQ_EXTI;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//MPW3 IRQ polarity is high by default
	EXTI_InitStructure.EXTI_LineCmd = DECAIRQ_EXTI_NOIRQ;
	EXTI_Init(&EXTI_InitStructure);*/
	EMBARC_PRINTF("\r\n The NVIC_DisableDECAIRQ is used. \r\n");
	return 0;
}

//中断使能，要改的！！！！！！！！！！！！！！！！！
int NVIC_Configuration(void)
{
/*
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Enable GPIO used as DECA IRQ for interrupt
	GPIO_InitStructure.GPIO_Pin = DECAIRQ;
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_IPD;	//IRQ pin should be Pull Down to prevent unnecessary EXT IRQ while DW1000 goes to sleep mode
	GPIO_Init(DECAIRQ_GPIO, &GPIO_InitStructure);

	 Connect EXTI Line to GPIO Pin
	GPIO_EXTILineConfig(DECAIRQ_EXTI_PORT, DECAIRQ_EXTI_PIN);

	 Configure EXTI line
	EXTI_InitStructure.EXTI_Line = DECAIRQ_EXTI;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//MPW3 IRQ polarity is high by default
	EXTI_InitStructure.EXTI_LineCmd = DECAIRQ_EXTI_USEIRQ;
	EXTI_Init(&EXTI_InitStructure);

	 Set NVIC Grouping to 16 groups of interrupt without sub-grouping
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	 Enable and set EXTI Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = DECAIRQ_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DECAIRQ_EXTI_USEIRQ;

	NVIC_Init(&NVIC_InitStructure);

	 Enable the RTC Interrupt
	//NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	//NVIC_Init(&NVIC_InitStructure);
*/
	EMBARC_PRINTF("\r\n The NVIC_Configuration is used. \r\n");
	return 0;
}

void SPI_ChangeRate(void *scalingfactor)
{
//	EMBARC_PRINTF("\r\n The SPI_ChangeRate is used! \r\n");

	DWM1000_port->spi_control(SPI_CMD_MST_SET_FREQ, scalingfactor);

//    EMBARC_PRINTF("\r\n The SPI_ChangeRate has used. \r\n");
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
//    EMBARC_PRINTF("\r\n The spi_set_rate_low is 2500000. \r\n");
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
	uint32_t rate_high = 1000000U;//只发送，最大6.25MHz；既发送又接收，最大5MHz
    SPI_ChangeRate(CONV2VOID(rate_high));
//    EMBARC_PRINTF("\r\n The spi_set_rate_high is 19000000. \r\n");
}

/**
 * @brief get current system time in millisecond
 * @return  millisecond
 */
uint32_t timer_read_ms(void)
{
	return OSP_GET_CUR_MS();
}

/*
void SPI_ConfigFastRate(uint16_t scalingfactor)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_I2S_DeInit(SPIx);

	// SPIx Mode setup
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	 //
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //
	//SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = scalingfactor; //sets BR[2:0] bits - baudrate in SPI_CR1 reg bits 4-6
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPIx, &SPI_InitStructure);

	// Enable SPIx
	SPI_Cmd(SPIx, ENABLE);
}

int SPI_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	SPI_I2S_DeInit(SPIx);

	// SPIx Mode setup
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	 //
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //
	//SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //sets BR[2:0] bits - baudrate in SPI_CR1 reg bits 4-6
	SPI_InitStructure.SPI_BaudRatePrescaler = SPIx_PRESCALER;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPIx, &SPI_InitStructure);

	// SPIx SCK and MOSI pin setup
	GPIO_InitStructure.GPIO_Pin = SPIx_SCK | SPIx_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);

	// SPIx MISO pin setup
	GPIO_InitStructure.GPIO_Pin = SPIx_MISO;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;

	GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);

	// SPIx CS pin setup
	GPIO_InitStructure.GPIO_Pin = SPIx_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIx_CS_GPIO, &GPIO_InitStructure);

	// Disable SPIx SS Output
	SPI_SSOutputCmd(SPIx, DISABLE);

	// Enable SPIx
	SPI_Cmd(SPIx, ENABLE);

	// Set CS high
	GPIO_SetBits(SPIx_CS_GPIO, SPIx_CS);

    return 0;
}


int SPI2_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	SPI_I2S_DeInit(SPIy);

	// SPIy Mode setup
	//SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	 //
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //
	//SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPIy_PRESCALER;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPIy, &SPI_InitStructure);

	// SPIy SCK and MOSI pin setup
	GPIO_InitStructure.GPIO_Pin = SPIy_SCK | SPIy_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

	// SPIy MISO pin setup
	GPIO_InitStructure.GPIO_Pin = SPIy_MISO;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;

	GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

	// SPIy CS pin setup
	GPIO_InitStructure.GPIO_Pin = SPIy_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIy_CS_GPIO, &GPIO_InitStructure);

	// Disable SPIy SS Output
	SPI_SSOutputCmd(SPIy, DISABLE);

	// Enable SPIy
	SPI_Cmd(SPIy, ENABLE);

	// Set CS high
	GPIO_SetBits(SPIy_CS_GPIO, SPIy_CS);

	// LCD_RS pin setup
	GPIO_InitStructure.GPIO_Pin = LCD_RS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

	// LCD_RW pin setup
	GPIO_InitStructure.GPIO_Pin = LCD_RW;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

    return 0;
}*/


//uint8_t Work_Mode;


void DWM1000_spi_init(void)
{
	uint32_t DWM1000_status;
	uint32_t DWM1000_DFS = 8;
//	DEV_SPI_TRANSFER dev_spi_xfer;
//	msg[0] = (uint8_t)(((addr >> 3) & 0x7F) | 0x80);
//	msg[1] = (uint8_t)((addr << 5) & 0xE0);
//	DEV_SPI_XFER_SET_TXBUF(&dev_spi_xfer, msg, 0, 2);
//	DEV_SPI_XFER_SET_RXBUF(&dev_spi_xfer, &ret_val, 2, 1);
//	DEV_SPI_XFER_SET_NEXT(&dev_spi_xfer, NULL);
//	DWM1000_port->spi_control(SPI_CMD_TRANSFER_POLLING, CONV2VOID(&dev_spi_xfer));

	DWM1000_port = spi_get_dev(DW_SPI_0_ID);

//	DWM1000_port->spi_info.freq = 2000000U;
//	DWM1000_port->spi_info.clk_mode = SPI_CLK_MODE_3;

	DWM1000_port->spi_control(SPI_CMD_GET_STATUS, CONV2VOID(DWM1000_status));
//	EMBARC_PRINTF("\r\n  DWM1000_status is %d. \r\n",DWM1000_status);


	//EMBARC_PRINTF("\r\n  hi = %d \r\n",DWM1000_port->spi_open(DWM1000_port->spi_info.mode, DWM1000_port->spi_info.freq));
	if (DWM1000_port->spi_open(DWM1000_port->spi_info.mode, DWM1000_port->spi_info.freq) == E_OK) {
		DWM1000_port->spi_control(SPI_CMD_GET_STATUS, CONV2VOID(DWM1000_status));
//		EMBARC_PRINTF("\r\n  DWM1000_status is %d. \r\n",DWM1000_status);

		DWM1000_port->spi_control(SPI_CMD_MST_SET_FREQ, CONV2VOID(1000000U));
		DWM1000_port->spi_control(SPI_CMD_SET_CLK_MODE, CONV2VOID(SPI_CLK_MODE_0));
//		DWM1000_port->spi_control(SPI_CMD_SET_DFS, CONV2VOID(DWM1000_DFS));
		DWM1000_port->spi_control(SPI_CMD_ENA_DEV, CONV2VOID(NULL));
		DWM1000_port->spi_control(SPI_CMD_MST_SEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));


//		EMBARC_PRINTF("\r\n  DWM1000_port' spi open is OK. \r\n");
//		EMBARC_PRINTF("\r\n  DWM1000_port' spi_info.mode is %d. \r\n",DWM1000_port->spi_info.mode);
//		EMBARC_PRINTF("\r\n  DWM1000_port' spi_info.freq is %d. \r\n",DWM1000_port->spi_info.freq);
	}
//	return 0;
}

void DWM1000_gpio_open(void)
{
	DWM1000_res = gpio_get_dev(DEV_GPIO_PORT_C);
	//EMSK_GPIO_CHECK_EXP_NORTN(LN298_port != NULL);
	if (DWM1000_res->gpio_open(DEV_GPIO_PORT_C) == E_OPNED) {
		DWM1000_res->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(EMSK_DWM1000_RES_MASK));
//		EMBARC_PRINTF("\r\n  DWM1000_port' gpio open is OK. \r\n");
	}


//	DWM1000_CS = gpio_get_dev(DEV_GPIO_PORT_C);
//	if (DWM1000_CS->gpio_open(DEV_GPIO_PORT_C) == E_OPNED) {
//		DWM1000_CS->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(EMSK_DWM1000_CS_MASK));
//		EMBARC_PRINTF("\r\n  DWM1000_port' gpio open is OK. \r\n");
//	}

	led_write(0x0001, BOARD_LED_MASK);
//	DWM1000_res->gpio_write(1 << EMSK_DWM1000_RES_OFFSET,(uint32_t)EMSK_DWM1000_RES_MASK);
//	EMBARC_PRINTF("\r\n The DWM1000 is finished. \r\n");
//error_exit:
//	return;
}


//中断初始化//
//void DWM1000_IRQ_open(void)
//{
//	DWM1000_IRQ = gpio_get_dev(DEV_GPIO_PORT_A);
//
//	DWM1000_get_echo.int_bit_ofs=DWM1000_IRQ_offset;
//	DWM1000_get_echo.int_bit_handler=DWM1000_echo_isr;
//
//	DWM1000_set_echo.int_bit_debounce = GPIO_INT_BIT_ENA_DEBOUNCE(DWM1000_IRQ_offset);//去抖；
//	DWM1000_set_echo.int_bit_mask = DWM1000_IRQ_mask;
//	DWM1000_set_echo.int_bit_polarity = GPIO_INT_BIT_POL_RISE_EDGE(DWM1000_IRQ_offset);
//	DWM1000_set_echo.int_bit_type = GPIO_INT_BIT_EDGE_TRIG(DWM1000_IRQ_offset);
//
//	DWM1000_IRQ ->gpio_open((uint32_t)(1<<DWM1000_IRQ_offset));
//
//	DWM1000_IRQ->gpio_control(GPIO_CMD_SET_BIT_DIR_INPUT, (void *)(DWM1000_IRQ_mask));
//	DWM1000_IRQ->gpio_control(GPIO_CMD_SET_BIT_INT_CFG, (void *)&DWM1000_set_echo);
//	DWM1000_IRQ->gpio_control(GPIO_CMD_SET_BIT_ISR, (void *)&DWM1000_get_echo);
//	DWM1000_IRQ->gpio_control(GPIO_CMD_ENA_BIT_INT, (void *)(DWM1000_IRQ_mask));
//
//	//EMSK_GPIO_CHECK_EXP_NORTN(LN298_port != NULL);
//
//	//EMBARC_PRINTF("\r\n The DEV_GPIO_PORT_A is %d \r\n",port_res->gpio_open(DEV_GPIO_PORT_A));
////	if (DWM1000_IRQ->gpio_open(DEV_GPIO_PORT_A) == E_OK) {
////		DWM1000_IRQ->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(EMSK_DWM1000_IRQ_MASK));
////		EMBARC_PRINTF("\r\n  DWM1000_port' IRQ open is OK. \r\n");
////	}
//
//}

//复位
void reset_DW1000(void)
{
	uint32_t pmod3_A = 0;

	DWM1000_res->gpio_write(pmod3_A << EMSK_DWM1000_RES_OFFSET,(uint32_t)EMSK_DWM1000_RES_MASK);
//	EMBARC_PRINTF("\r\n The DWM1000_res is LOW \r\n");
	deca_sleep(5);//正常值是3ms
	DWM1000_res->gpio_write(~pmod3_A << EMSK_DWM1000_RES_OFFSET,(uint32_t)EMSK_DWM1000_RES_MASK);
//	EMBARC_PRINTF("\r\n The DWM1000_res is HIGH \r\n");
    deca_sleep(5);
//    EMBARC_PRINTF("\r\n The DWM1000_res is finish \r\n");
}


void setup_DW1000RSTnIRQ(int enable)
{
	EMBARC_PRINTF("\r\n The setup_DW1000RSTnIRQ is used. \r\n");
	/*GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	if(enable)
	{
		// Enable GPIO used as DECA IRQ for interrupt
		GPIO_InitStructure.GPIO_Pin = DECARSTIRQ;
		//GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_IPD;	//IRQ pin should be Pull Down to prevent unnecessary EXT IRQ while DW1000 goes to sleep mode
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(DECARSTIRQ_GPIO, &GPIO_InitStructure);

		 Connect EXTI Line to GPIO Pin
		GPIO_EXTILineConfig(DECARSTIRQ_EXTI_PORT, DECARSTIRQ_EXTI_PIN);

		 Configure EXTI line
		EXTI_InitStructure.EXTI_Line = DECARSTIRQ_EXTI;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//MP IRQ polarity is high by default
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		 Set NVIC Grouping to 16 groups of interrupt without sub-grouping
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

		 Enable and set EXTI Interrupt to the lowest priority
		NVIC_InitStructure.NVIC_IRQChannel = DECARSTIRQ_EXTI_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure);
	}
	else
	{
		//put the pin back to tri-state ... as input
		GPIO_InitStructure.GPIO_Pin = DW1000_RSTn;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DW1000_RSTn_GPIO, &GPIO_InitStructure);

		 Configure EXTI line
		EXTI_InitStructure.EXTI_Line = DECARSTIRQ_EXTI;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//MP IRQ polarity is high by default
		EXTI_InitStructure.EXTI_LineCmd = DISABLE;
		EXTI_Init(&EXTI_InitStructure);
	}*/
}


int ETH_GPIOConfigure(void)
{
	EMBARC_PRINTF("\r\n The ETH_GPIOConfigure is used. \r\n");
/*
#if 0
	GPIO_InitTypeDef GPIO_InitStructure;

	 ETHERNET pins configuration
	 AF Output Push Pull:
	- ETH_MII_MDIO / ETH_RMII_MDIO: PA2
	- ETH_MII_MDC / ETH_RMII_MDC: PC1
	- ETH_MII_TXD2: PC2
	- ETH_MII_TX_EN / ETH_RMII_TX_EN: PB11
	- ETH_MII_TXD0 / ETH_RMII_TXD0: PB12
	- ETH_MII_TXD1 / ETH_RMII_TXD1: PB13
	- ETH_MII_PPS_OUT / ETH_RMII_PPS_OUT: PB5
	- ETH_MII_TXD3: PB8

	 Configure PA2 as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	 Configure PC1 and PC2 as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	 Configure PB5, PB8, PB11, PB12 and PB13 as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_11 |
								GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	************************************************************
	               For Remapped Ethernet pins
	***********************************************************
	 Input (Reset Value):
	- ETH_MII_CRS CRS: PA0
	- ETH_MII_RX_CLK / ETH_RMII_REF_CLK: PA1
	- ETH_MII_COL: PA3
	- ETH_MII_RX_DV / ETH_RMII_CRS_DV: PD8
	- ETH_MII_TX_CLK: PC3
	- ETH_MII_RXD0 / ETH_RMII_RXD0: PD9
	- ETH_MII_RXD1 / ETH_RMII_RXD1: PD10
	- ETH_MII_RXD2: PD11
	- ETH_MII_RXD3: PD12
	- ETH_MII_RX_ER: PB10

	 Configure PA0, PA1 and PA3 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	 Configure PB10 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	 Configure PC3 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	 Configure PD8, PD9, PD10, PD11 and PD12 as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);



	 MCO pin configuration-------------------------------------------------
	 Configure MCO (PA8) as alternate function push-pull
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
*/
	return 0;
}


/*int is_IRQ_enabled(void)
{
	return ((   NVIC->ISER[((uint32_t)(DECAIRQ_EXTI_IRQn) >> 5)]
	           & (uint32_t)0x01 << (DECAIRQ_EXTI_IRQn & (uint8_t)0x1F)  ) ? 1 : 0) ;
}*/

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
	DWM1000_gpio_open();
	DWM1000_spi_init();
//	DWM1000_IRQ_open();
}


