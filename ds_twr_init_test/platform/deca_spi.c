/*! ----------------------------------------------------------------------------
 * @file	deca_spi.c
 * @brief	SPI access functions
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */
#include <string.h>

#include "embARC_debug.h"
#include "deca_spi.h"
#include "deca_sleep.h"
#include "deca_device_api.h"
#include "port.h"

extern DEV_SPI_PTR DWM1000_port;

int writetospi_serial( uint16_t headerLength,
			   	    const uint8_t *headerBuffer,
					uint32_t bodylength,
					const uint8_t *bodyBuffer
				  );

int readfromspi_serial( uint16_t	headerLength,
			    	 const uint8_t *headerBuffer,
					 uint32_t readlength,
					 uint8_t *readBuffer );
/*! ------------------------------------------------------------------------------------------------------------------
 * Function: openspi()
 *
 * Low level abstract function to open and initialise access to the SPI device.
 * returns 0 for success, or -1 for error
 */
int openspi(/*SPI_TypeDef* SPIx*/)
{
	// done by port.c, default SPI used is SPI1

	return 0;

} // end openspi()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: closespi()
 *
 * Low level abstract function to close the the SPI device.
 * returns 0 for success, or -1 for error
 */
int closespi(void)
{
//	while (port_SPIx_busy_sending()); //wait for tx buffer to empty
//
//	port_SPIx_disable();
	if(DWM1000_port->spi_close() == E_OK)
		EMBARC_PRINTF("\r\n  DWM1000_port' spi close is OK. \r\n");
	return 0;

} // end closespi()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */
#pragma GCC optimize ("O3")
int writetospi_serial
(
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       bodylength,
    const uint8_t *bodyBuffer
)
{
	DEV_SPI_PTR spi_write;
	DEV_SPI_TRANSFER spi_header;
	DEV_SPI_TRANSFER spi_body;
	int32_t ercd = 0;
	int32_t ret0, ret1, ret2;

	spi_write = spi_get_dev(DW_SPI_0_ID);

//	DEV_SPI_XFER_SET_TXBUF(xfer, buf, ofs, len)
	DEV_SPI_XFER_SET_TXBUF(&spi_header, headerBuffer, 0, headerLength);
	DEV_SPI_XFER_SET_RXBUF(&spi_header, NULL, headerLength, 0);
	DEV_SPI_XFER_SET_NEXT(&spi_header, &spi_body);

	DEV_SPI_XFER_SET_TXBUF(&spi_body, bodyBuffer, 0, bodylength);
	DEV_SPI_XFER_SET_RXBUF(&spi_body, NULL, bodylength, 0);
	DEV_SPI_XFER_SET_NEXT(&spi_body, NULL);

	ret0 = spi_write->spi_control(SPI_CMD_MST_SEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
	ret1 = spi_write->spi_control(SPI_CMD_TRANSFER_POLLING, CONV2VOID(&spi_header));
	ret2 = spi_write->spi_control(SPI_CMD_MST_DSEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
//	EMBARC_PRINTF("\r\n  DWM1000_port' read ret0 is %d, ret1 is %d, ret2 is %d. \r\n",ret0, ret1, ret2);


//	ret0 = spi_flash->spi_control(SPI_CMD_MST_SEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
//	ret1 = spi_flash->spi_control(SPI_CMD_TRANSFER_POLLING, CONV2VOID(&spi_body));
//	ret2 = spi_flash->spi_control(SPI_CMD_MST_DSEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
////	EMBARC_PRINTF("\r\n  DWM1000_port' read ret0 is %d, ret1 is %d, ret2 is %d. \r\n",ret0, ret1, ret2);

	if (!((ret0 == E_OK) && (ret1 == E_OK) && (ret2 == E_OK)))
	{
		ercd = E_SYS;
	}
	else
	{
		ercd = E_OK;
	}
	//还有中断没写

    return ercd;
} // end writetospi()


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */
#pragma GCC optimize ("O3")
int readfromspi_serial
(
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       readlength,
    uint8_t       *readBuffer
)
{
	DEV_SPI_PTR spi_read;
	DEV_SPI_TRANSFER spi_header;
	DEV_SPI_TRANSFER spi_body;
	int32_t ercd = 0;
	int32_t ret0, ret1, ret2;

	spi_read = spi_get_dev(DW_SPI_0_ID);

//	DEV_SPI_XFER_SET_TXBUF(xfer, buf, ofs, len)
//	DEV_SPI_XFER_SET_TXBUF(&spi_flash->spi_info.xfer, headerBuffer, 0, headerLength);
//	DEV_SPI_XFER_SET_RXBUF(&spi_flash->spi_info.xfer, readBuffer, headerLength, readlength);
//	DEV_SPI_XFER_SET_NEXT(&spi_flash->spi_info.xfer, NULL);
	DEV_SPI_XFER_SET_TXBUF(&spi_header, headerBuffer, 0, headerLength);
	DEV_SPI_XFER_SET_RXBUF(&spi_header, NULL, headerLength, 0);
	DEV_SPI_XFER_SET_NEXT(&spi_header, &spi_body);

	DEV_SPI_XFER_SET_TXBUF(&spi_body, NULL, 0, readlength);
	DEV_SPI_XFER_SET_RXBUF(&spi_body, readBuffer, 0, readlength);
	DEV_SPI_XFER_SET_NEXT(&spi_body, NULL);


	ret0 = spi_read->spi_control(SPI_CMD_MST_SEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
//	ret1 = spi_read->spi_control(SPI_CMD_TRANSFER_POLLING, CONV2VOID(&spi_flash->spi_info.xfer));
	ret1 = spi_read->spi_control(SPI_CMD_TRANSFER_POLLING, CONV2VOID(&spi_header));
	ret2 = spi_read->spi_control(SPI_CMD_MST_DSEL_DEV, CONV2VOID(DEV_SPI_CS_LINE_0));
//	EMBARC_PRINTF("\r\n  DWM1000_port' read ret0 is %d, ret1 is %d, ret2 is %d. \r\n",ret0, ret1, ret2);
	if (!((ret0 == E_OK) && (ret1 == E_OK) && (ret2 == E_OK)))
	{
		ercd = E_SYS;
	}
	else
	{
		ercd = E_OK;
	}

	//还有中断没写

    return ercd;
} // end readfromspi()
