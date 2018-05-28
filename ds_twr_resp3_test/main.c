/*
 * main.c
 *
 *  Created on: 2018��5��25��
 *      Author: dj201
 */

#include "embARC.h"
#include "embARC_debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "deca_device_api.h"
#include "deca_regs.h"
#include "deca_sleep.h"
//#include "lcd.h"
#include "port.h"
//#include "FreeRTOSConfig.h"
#include "LN298.h"

extern int LN298_flag;

/* Example application name and version to display on LCD screen. */
#define APP_NAME "DS TWR RESP TEST"

/* Default communication configuration. We use here EVK1000's default mode (mode 3). */
static dwt_config_t config = {
    2,               /* Channel number. */
    DWT_PRF_64M,     /* Pulse repetition frequency. */
    DWT_PLEN_1024,   /* Preamble length. Used in TX only. */
    DWT_PAC32,       /* Preamble acquisition chunk size. Used in RX only. */
    9,               /* TX preamble code. Used in TX only. */
    9,               /* RX preamble code. Used in RX only. */
    1,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
    DWT_BR_110K,     /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};

/* Default antenna delay values for 64 MHz PRF. See NOTE 1 below. */
#define TX_ANT_DLY 16436//16520//16436
#define RX_ANT_DLY 16436

/* Frames used in the ranging process. See NOTE 2 below. */
static uint8 rx_poll_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'S', 'O', 'F', 'A', 0x21, 0, 0};
static uint8 tx_resp_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'F', 'A', 'S', '3', 0x10, 0x02, 0, 0, 0, 0};
static uint8 rx_final_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'S', 'O', 'F', 'A', 0x23, \
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint8 rx_s1_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'S', '3', 'S', '1', 0x24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8 rx_s2_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'S', '3', 'S', '2', 0x24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Length of the common part of the message (up to and including the function code, see NOTE 2 below). */
#define ALL_MSG_COMMON_LEN 10
/* Index to access some of the fields in the frames involved in the process. */
#define ALL_MSG_SN_IDX 2
#define FINAL_MSG_POLL_TX_TS_IDX 34
#define FINAL_MSG_RESP_RX_TS_IDX 38
#define FINAL_MSG_FINAL_TX_TS_IDX 42
#define FINAL_MSG_TS_LEN 4
/* Frame sequence number, incremented after each transmission. */
static uint8 frame_seq_nb = 0;
static uint8 test_loop = 0;
int initbad = 0;
/* Buffer to store received messages.
 * Its size is adjusted to longest frame that this example code is supposed to handle. */
#define RX_BUF_LEN 48
static uint8 rx_buffer[RX_BUF_LEN];

/* Hold copy of status register state here for reference so that it can be examined at a debug breakpoint. */
__IO static uint32 status_reg = 0;

/* UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) conversion factor.
 * 1 uus = 512 / 499.2 �s and 1 �s = 499.2 * 128 dtu. */
#define UUS_TO_DWT_TIME 65536

/* Delay between frames, in UWB microseconds. See NOTE 4 below. */
/* This is the delay from Frame RX timestamp to TX reply timestamp used for calculating/setting the DW1000's delayed TX function. This includes the
 * frame length of approximately 2.46 ms with above configuration. */
#define POLL_RX_TO_RESP_TX_DLY_UUS 8000
/* This is the delay from the end of the frame transmission to the enable of the receiver, as programmed for the DW1000's wait for response feature. */
#define RESP_TX_TO_FINAL_RX_DLY_UUS 5000//500
/* Receive final timeout. See NOTE 5 below. */
#define FINAL_RX_TIMEOUT_UUS 10000//3300
/* Preamble timeout, in multiple of PAC size. See NOTE 6 below. */
#define PRE_TIMEOUT 256

/* Timestamps of frames transmission/reception.
 * As they are 40-bit wide, we need to define a 64-bit int type to handle them. */
typedef signed long long int64;
typedef unsigned long long uint64;
static uint64 poll_rx_ts;
static uint64 resp_tx_ts;
static uint64 final_rx_ts;

/* Speed of light in air, in metres per second. */
#define SPEED_OF_LIGHT 299702547

/* Hold copies of computed time of flight and distance here for reference so that it can be examined at a debug breakpoint. */
static double tof;
static double dis1;
static double dis2;
static double dis3;
static double theta;

/* String used to display measured distance on LCD screen (16 characters maximum). */
char dist_str[16] = {0};

/* Declaration of static functions. */
static uint64 get_tx_timestamp_u64(void);
static uint64 get_rx_timestamp_u64(void);
static void final_msg_get_ts(const uint8 *ts_field, uint32 *ts);
static void msg_get(uint8 *msg, char *dis);

int main(void)
{
	peripherals_init();

	/* Display application name on LCD. */
	lcd_display_str(APP_NAME);

	/* Reset and initialise DW1000.
	 * For initialisation, DW1000 clocks must be temporarily set to crystal speed. After initialisation SPI rate can be increased for optimum
	 * performance. */
	reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
	spi_set_rate_low();//ʵ������Ϊ2.5MHz
	if (dwt_initialise(DWT_LOADUCODE) == DWT_ERROR)
	{
		lcd_display_str("INIT FAILED");
		while (1)
		{ };
	}
	spi_set_rate_high();//ʵ��Ϊ���ȶ����͵�1MHz��

	/* Configure DW1000. */
	dwt_configure(&config);

	/* Apply default antenna delay value.*/
	dwt_setrxantennadelay(RX_ANT_DLY);
	dwt_settxantennadelay(TX_ANT_DLY);

	/* Set preamble timeout for expected frames. */
	dwt_setpreambledetecttimeout(PRE_TIMEOUT);
	/* Loop forever responding to ranging requests. */
	while (1)
	{
		/* Clear reception timeout to start next ranging process. */
		dwt_setrxtimeout(0);

		/* Activate reception immediately. */
		dwt_rxenable(0);

		/* Poll for reception of a frame or error/timeout. See NOTE 8 below. */
		while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR)))
		{
			test_loop++;
			if(test_loop>500)
			{
				break;
			}
		};
		test_loop=0;

		if((status_reg & 0xffff0000) == 0xffff0000)
		{
			/* Start with board specific hardware init. */
			do{
				peripherals_init();
				reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
				spi_set_rate_low();
				initbad = dwt_initialise(DWT_LOADUCODE);
				if (initbad == DWT_ERROR)
				{
					lcd_display_str("INIT FAILED");
					sleep_ms(1000);
				}
			}while(initbad == DWT_ERROR);
			spi_set_rate_high();
			dwt_configure(&config);
			dwt_setrxantennadelay(RX_ANT_DLY);
			dwt_settxantennadelay(TX_ANT_DLY);
			dwt_setpreambledetecttimeout(PRE_TIMEOUT);
			continue;
		}

		if (status_reg & SYS_STATUS_RXFCG)
		{
			uint32 frame_len;

			/* Clear good RX frame event in the DW1000 status register. */
			dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_GOOD));

			/* A frame has been received, read it into the local buffer. */
			frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;
			if (frame_len <= RX_BUFFER_LEN)
			{
				dwt_readrxdata(rx_buffer, frame_len, 0);
			}
//            EMBARC_PRINTF("\r\n The len is %d,rx is %x,%x,%d,%x,%x,%c%c%c%c,%x,%d,%d,%d,%d \r\n",\
//            	frame_len,rx_buffer[0],rx_buffer[1],rx_buffer[2],rx_buffer[3],rx_buffer[4],rx_buffer[5],\
//				rx_buffer[6],rx_buffer[7],rx_buffer[8],rx_buffer[9],rx_buffer[10],rx_buffer[11],\
//				rx_buffer[12],rx_buffer[13]);

			/* Check that the frame is a poll sent by "DS TWR initiator" example.
			 * As the sequence number field of the frame is not relevant, it is cleared to simplify the validation of the frame. */
			rx_buffer[ALL_MSG_SN_IDX] = 0;
			if (memcmp(rx_buffer, rx_poll_msg, ALL_MSG_COMMON_LEN) == 0)
			{
				uint32 resp_tx_time;
				int ret;

				/* Retrieve poll reception timestamp. */
				poll_rx_ts = get_rx_timestamp_u64();
				/* Set send time for response. See NOTE 9 below. */
				resp_tx_time = (poll_rx_ts + (POLL_RX_TO_RESP_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;
				dwt_setdelayedtrxtime(resp_tx_time);

				/* Set expected delay and timeout for final message reception. See NOTE 4 and 5 below. */
				dwt_setrxaftertxdelay(RESP_TX_TO_FINAL_RX_DLY_UUS);
				dwt_setrxtimeout(FINAL_RX_TIMEOUT_UUS);

				/* Write and send the response message. See NOTE 10 below.*/
				tx_resp_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
				dwt_writetxdata(sizeof(tx_resp_msg), tx_resp_msg, 0); /* Zero offset in TX buffer. */
				dwt_writetxfctrl(sizeof(tx_resp_msg), 0); /* Zero offset in TX buffer, ranging. */

				ret = dwt_starttx(DWT_START_TX_DELAYED | DWT_RESPONSE_EXPECTED);

				/* If dwt_starttx() returns an error, abandon this ranging exchange and proceed to the next one. See NOTE 11 below. */
				if (ret == DWT_ERROR)
				{
					continue;
				}

				/* Poll for reception of expected "final" frame or error/timeout. See NOTE 8 below. */
				while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR)))
				{
					test_loop++;
					if(test_loop>500)
						break;
				};
				test_loop = 0;

				/* Increment frame sequence number after transmission of the response message (modulo 256). */
                frame_seq_nb++;

				if((status_reg & 0xffff0000) == 0xffff0000)
				{
					/* Start with board specific hardware init. */
					do{
						peripherals_init();
						reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
						spi_set_rate_low();
						initbad = dwt_initialise(DWT_LOADUCODE);
						if (initbad == DWT_ERROR)
						{
							lcd_display_str("INIT FAILED");
							sleep_ms(1000);
						}
					}while(initbad == DWT_ERROR);
					spi_set_rate_high();
					dwt_configure(&config);
					dwt_setrxantennadelay(RX_ANT_DLY);
					dwt_settxantennadelay(TX_ANT_DLY);
					dwt_setpreambledetecttimeout(PRE_TIMEOUT);
					continue;
				}

				if (status_reg & SYS_STATUS_RXFCG)
				{
					/* Clear good RX frame event and TX frame sent in the DW1000 status register. */
					dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_GOOD));

					/* A frame has been received, read it into the local buffer. */
					frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
					if (frame_len <= RX_BUF_LEN)
					{
						dwt_readrxdata(rx_buffer, frame_len, 0);
					}
//                    EMBARC_PRINTF("\r\n The len is %d,rx is %x,%x,%d,%x,%x,%c%c%c%c,%x,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \r\n",\
//						frame_len,rx_buffer[0],rx_buffer[1],rx_buffer[2],rx_buffer[3],rx_buffer[4],rx_buffer[5],\
//						rx_buffer[6],rx_buffer[7],rx_buffer[8],rx_buffer[9],rx_buffer[10],rx_buffer[11],\
//						rx_buffer[12],rx_buffer[13],rx_buffer[14],rx_buffer[15],rx_buffer[16],rx_buffer[17],\
//						rx_buffer[18],rx_buffer[19],rx_buffer[20],rx_buffer[21],rx_buffer[22],rx_buffer[23]);

					/* Check that the frame is a final message sent by "DS TWR initiator" example.
					 * As the sequence number field of the frame is not used in this example, it can be zeroed to ease the validation of the frame. */
					rx_buffer[ALL_MSG_SN_IDX] = 0;
					if (memcmp(rx_buffer, rx_final_msg, ALL_MSG_COMMON_LEN) == 0)
					{
						uint32 poll_tx_ts, resp_rx_ts, final_tx_ts;
						uint32 poll_rx_ts_32, resp_tx_ts_32, final_rx_ts_32;
						double Ra, Rb, Da, Db;
						int64 tof_dtu;

						/* Retrieve response transmission and final reception timestamps. */
						resp_tx_ts = get_tx_timestamp_u64();
						final_rx_ts = get_rx_timestamp_u64();

						/* Get timestamps embedded in the final message. */
						final_msg_get_ts(&rx_buffer[FINAL_MSG_POLL_TX_TS_IDX], &poll_tx_ts);
						final_msg_get_ts(&rx_buffer[FINAL_MSG_RESP_RX_TS_IDX], &resp_rx_ts);
						final_msg_get_ts(&rx_buffer[FINAL_MSG_FINAL_TX_TS_IDX], &final_tx_ts);

						/* Compute time of flight. 32-bit subtractions give correct answers even if clock has wrapped. See NOTE 12 below. */
						poll_rx_ts_32 = (uint32)poll_rx_ts;
						resp_tx_ts_32 = (uint32)resp_tx_ts;
						final_rx_ts_32 = (uint32)final_rx_ts;
						Ra = (double)(resp_rx_ts - poll_tx_ts);
						Rb = (double)(final_rx_ts_32 - resp_tx_ts_32);
						Da = (double)(final_tx_ts - resp_rx_ts);
						Db = (double)(resp_tx_ts_32 - poll_rx_ts_32);
						tof_dtu = (int64)((Ra * Rb - Da * Db) / (Ra + Rb + Da + Db));

						tof = tof_dtu * DWT_TIME_UNITS;
						dis3 = tof * SPEED_OF_LIGHT;

						/* Display computed distance on LCD. */
						sprintf(dist_str, "DIST3: %2.2f m", dis3);
						lcd_display_str("\r\n %s",dist_str);

						LN298_flag = 50;
						if (dis3 > 1.2)
						{
							lcd_display_str("  dis > 1.2m");
							LN298_forward();
						}
						else if (dis3 <= 1)
						{
							lcd_display_str("  dis <= 1m");
							LN298_back();
						}
						else
						{
							lcd_display_str("  1m < dis <= 1.2m");
							LN298_stop();
						}

						/* Clear RX error/timeout events in the DW1000 status register. */
						dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_GOOD | SYS_STATUS_ALL_RX_ERR));

						/* Reset RX to properly reinitialise LDE operation. */
						dwt_rxreset();
					}
				}
				else
				{
					/* Clear RX error/timeout events in the DW1000 status register. */
					dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_ERR));

					/* Reset RX to properly reinitialise LDE operation. */
					dwt_rxreset();
				}
			}
			else
			{
				/* Clear RX error/timeout events in the DW1000 status register. */
				dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_ERR));

				/* Reset RX to properly reinitialise LDE operation. */
				dwt_rxreset();
			}
		}
		else
		{
			/* Clear RX error/timeout events in the DW1000 status register. */
			dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_TX | SYS_STATUS_ALL_RX_ERR));

			/* Reset RX to properly reinitialise LDE operation. */
			dwt_rxreset();
		}
	}
	return 0;
}


/*! ------------------------------------------------------------------------------------------------------------------
 * @fn get_tx_timestamp_u64()
 *
 * @brief Get the TX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_tx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readtxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn get_rx_timestamp_u64()
 *
 * @brief Get the RX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_rx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readrxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn final_msg_get_ts()
 *
 * @brief Read a given timestamp value from the final message. In the timestamp fields of the final message, the least
 *        significant byte is at the lower address.
 *
 * @param  ts_field  pointer on the first byte of the timestamp field to read
 *         ts  timestamp value
 *
 * @return none
 */
static void final_msg_get_ts(const uint8 *ts_field, uint32 *ts)
{
    int i;
    *ts = 0;
    for (i = 0; i < FINAL_MSG_TS_LEN; i++)
    {
        *ts += ts_field[i] << (i * 8);
    }
}

static void msg_get(uint8 *msg, char *dis)
{
	int j;
    for (j = 0; j < 9; j++)
    {
    	dis[j] = msg[ALL_MSG_COMMON_LEN + j];
    }
}
