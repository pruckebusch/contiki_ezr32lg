#include "../net/radio-arch.h"

// ToDo
// move application preferences from radio drivers to radio-arch-config.h

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

// define process
PROCESS(ezradio_process, "Radio driver process");

#define EZRADIO_MAX_PAYLOAD_SIZE	64
#define CLEAR_RXBUF()           	(ezradio_rxbuf[0] = 0)
#define IS_RXBUF_EMPTY()        	(ezradio_rxbuf[0] == 0)

static int ezradio_init(void);
static int ezradio_prepare(const void *payload, unsigned short payload_len);
static int ezradio_transmit(unsigned short payload_len);
static int ezradio_send(const void *data, unsigned short len);
static int ezradio_read(void *buf, unsigned short bufsize);
static int ezradio_channel_clear(void);
static int ezradio_receiving_packet(void);
static int ezradio_pending_packet(void);
static int ezradio_on(void);
static int ezradio_off(void);

static void ezradioPowerUp(void);
static void ezradio_start_rx_listening(void);

const struct radio_driver ezradio_driver = {
  ezradio_init,
  ezradio_prepare,
  ezradio_transmit,
  ezradio_send,
  ezradio_read,
  ezradio_channel_clear,
  ezradio_receiving_packet,
  ezradio_pending_packet,
  ezradio_on,
  ezradio_off,
};

// EZRadio driver init data and handler
EZRADIODRV_HandleData_t appRadioInitData = EZRADIO_CONFIG;
EZRADIODRV_Handle_t appRadioHandle = &appRadioInitData;
ezradio_cmd_reply_t ezradioReply;

// Radio configuration data array.
static const uint8_t Radio_Configuration_Data_Array[]  = RADIO_CONFIGURATION_DATA_ARRAY;

static uint8_t ezradio_rxbuf[EZRADIO_MAX_PAYLOAD_SIZE];
static int packet_is_prepared = 0;
static const void *packet_payload;
static unsigned short packet_payload_len = 0;
static packetbuf_attr_t last_rssi = 0;

static void GPIO_EZRadio_INT_IRQHandler( uint8_t pin ) {
	ezradio_cmd_reply_t radioReplyData;
	EZRADIODRV_ReplyHandle_t radioReplyHandle = &radioReplyData;

	// Read ITs, clear all pending ones
	ezradio_get_int_status(0u, 0u, 0u, radioReplyHandle);

	if (radioReplyHandle->GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT) {
		PRINTF("PACKET IRQ: Rx packet \n");
		process_poll(&ezradio_process);
	} else if (radioReplyHandle->GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_CRC_ERROR_PEND_BIT) {
		// CRC callback
		// Should be handled by Contiki
		PRINTF("PACKET IRQ: CRC Error \n");
	} else if (radioReplyHandle->GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		// Tx IRQ
	}

	// continue receiving
	ezradio_start_rx_listening();
}

static int ezradio_init(void) {
	// SPI and IRQ init
	ezradio_hal_GpioInit(GPIO_EZRadio_INT_IRQHandler, true);
	ezradio_hal_SpiInit();

	// power Up the radio chip
	ezradioPowerUp();

	// load radio configuration
	while (EZRADIO_CONFIG_SUCCESS != ezradio_configuration_init(Radio_Configuration_Data_Array)) {
		printf("ERROR: Radio configuration failed!\n");

		USTIMER_Init();
		// delay for 10ms time
		USTIMER_Delay(10000u);
		// deinit ustimer
		USTIMER_DeInit();

		// power Up the radio chip
		ezradioPowerUp();
	}

	// Read ITs, clear pending ones
	ezradio_get_int_status(0u, 0u, 0u, NULL);

	ezradio_part_info(&ezradioReply);
	printf("Device: Si%04x\n\n", ezradioReply.PART_INFO.PART);

	process_start(&ezradio_process, NULL);

	PRINTF("Radio initialized\n");

	return 1;
}

// prepares a packet to be sent by the radio
static int ezradio_prepare(const void *payload, unsigned short payload_len) {
	packet_is_prepared = 0;

	// checks if the payload length is supported
	if (payload_len > PLATFORM_MAX_PAYLOAD_SIZE) {
		PRINTF("Payload exceeds max payload size \n");
		return 0;
	}

	PRINTF("> %d \n\r", payload_len);
	PRINTF("payload contents : \n\r");
	int i;
	for (i = 0; i < payload_len; i++) {
		PRINTF("%d ", ((uint8_t * )payload)[i]);
		if ((i % 16) == 15)
			PRINTF("\n\r");
	}
	PRINTF("\n\r");

	// flush fifo
	ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_TX_BIT, NULL);

	packet_payload = payload;
	packet_payload_len = payload_len;

	ezradio_request_device_state(&ezradioReply);

	while(ezradioReply.REQUEST_DEVICE_STATE.CURR_STATE == EZRADIO_CMD_REQUEST_DEVICE_STATE_REP_CURR_STATE_MAIN_STATE_ENUM_TX) {
		PRINTF("Device not ready!\n");
		ezradio_request_device_state(&ezradioReply);
	}

	PRINTF("Device READY \n");

	// fill the TX fifo with data
	ezradio_write_tx_fifo(appRadioHandle->packetTx.lenConfig.pktLen, payload);

	packet_is_prepared = 1;

	PRINTF("RADIO prepare out \n");

	return RADIO_TX_OK;
}

// sends the previously prepared packet
static int ezradio_transmit(unsigned short payload_len) {
	PRINTF("RADIO TRANSMIT IN \n");

	ezradio_cmd_reply_t radioReplyData;
	EZRADIODRV_ReplyHandle_t radioReplyHandle = &radioReplyData;

	ezradio_start_tx(appRadioHandle->packetTx.channel, 0x30, (uint16_t) payload_len);

	PRINTF("TX started \n");

	// get pending IRQ's
	// do not continue while transmission is still going on
	ezradio_get_int_status(0x0, 0x0, 0x0, radioReplyHandle);

	while (radioReplyHandle->GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		ezradio_get_int_status(0x0, 0x0, 0x0, radioReplyHandle);
	}

	PRINTF("Packet TRANSMITTED with length %d \n", payload_len);

	return RADIO_TX_OK;
}

// prepares & transmits a packet
static int ezradio_send(const void *data, unsigned short len) {
	PRINTF("SEND PACKAGE with %d bytes \n", len);
	if (ezradio_prepare(data, len) == RADIO_TX_ERR) {
		return RADIO_TX_ERR;
	}
	return ezradio_transmit(len);
}

// copies a received packet to Contiki’s input buffer.
static int ezradio_read(void *buf, unsigned short bufsize) {
	PRINTF("Radio READ IN\n");

	// read the contents of the fifo into local radio reply
	ezradio_cmd_reply_t radioReplyLocal;
	// check how many bytes we received.
	ezradio_fifo_info(0u, &radioReplyLocal);
	// Read out the RX FIFO content.
	bufsize = radioReplyLocal.FIFO_INFO.RX_FIFO_COUNT;

	PRINTF("RECEIVED %d bytes \n", bufsize);

	ezradio_read_rx_fifo(bufsize, (uint8_t *) buf);

	// flush FIFO
	ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_RX_BIT, NULL);

	PRINTF("Radio READ OUT\n");

	return (int) bufsize;
}

// performs a Clear Channel Assessment (CCA) to find out if another device is currently transmitting.
static int ezradio_channel_clear(void) {
	PRINTF("Radio CHANNEL CLEAR IN\n");
	PRINTF("Radio CHANNEL CLEAR OUT\n");
}

// checks if the radio driver is currently receiving a packet
static int ezradio_receiving_packet(void) {
	return 0;
}

// checks if the radio driver has just received a packet
static int ezradio_pending_packet(void) {
	PRINTF("Radio PENDING PACKET\n");
}

// turns the radio on
// command fired on startup
static int ezradio_on(void) {
	ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_RX_BIT, NULL);
	ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_TX_BIT, NULL);
	ezradio_start_rx_listening();

	PRINTF("Radio on \n");

	return 1;
}

// turns the radio off (or go to into Low Power Mode).
static int ezradio_off(void) {
	PRINTF("Radio off \n");

	return 0;
}

// receive thread
PROCESS_THREAD(ezradio_process, ev, data)
{
  PROCESS_BEGIN();

  PRINTF("Radio driver process started\n");
  int len;

  while(1) {
		PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_POLL);

		PRINTF("EZRadio polled\n");

		// clear packet buffer
	    packetbuf_clear();
	    // read received data in Contiki's packet buffer & notify Contiki about a new packet
	    len = ezradio_read(packetbuf_dataptr(), PACKETBUF_SIZE);
	    packetbuf_set_datalen(len);
	    NETSTACK_RDC.input();

	    // ToDo
	    // if buffer not empty
	    // poll again

	    uint8_t *datar;
		datar = packetbuf_dataptr();

	   PRINTF("< %d :\n", len);
		PRINTF("Received payload contents :\n\r");
		int i;
		for (i = 0; i < len; i++) {
			PRINTF("%d ", ((uint8_t * )datar)[i]);
			if ((i % 16) == 15)
				PRINTF("\n\r");
		}
		PRINTF("\n\r");

		// flush TX FIFO
		ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_TX_BIT, NULL);

		ezradio_on();
  }

  PROCESS_END();
}

static void ezradio_start_rx_listening(void) {
	ezradio_start_rx(appRadioHandle->packetRx.channel, 0u, 0u,
			EZRADIO_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
			EZRADIO_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
			EZRADIO_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX);
}

static void ezradioPowerUp(void) {
  /* Hardware reset the chip */
  ezradio_reset();

  /* Initialize ustimer */
  USTIMER_Init();
  /* Delay for preconfigured time */
  USTIMER_Delay( RADIO_CONFIG_DATA_RADIO_DELAY_AFTER_RESET_US );
  /* Deinit ustimer */
  USTIMER_DeInit();
}
