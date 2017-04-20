#include "contiki.h"
#include <stdlib.h>
#include "sys/energest.h"

#include <efm32.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "uart0.h"
#include "dev/watchdog.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

static int (*uart0_input_handler)(unsigned char c);

void UART0_RX_IRQHandler(void) {
	unsigned char c;

	ENERGEST_ON(ENERGEST_TYPE_IRQ);

	if (UART0->STATUS & UART_STATUS_RXDATAV) {

		c = USART_Rx(UART0);
		if (uart0_input_handler != NULL)
			uart0_input_handler(c);
	}

	ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}

uint8_t uart0_active(void) {
	return 0;
}

void uart0_set_input(int (*input)(unsigned char c)) {
	uart0_input_handler = input;
}

int *uart0_get_input(void) {
	return (int*) uart0_input_handler;
}

void uart0_writeb(unsigned char c) {
	watchdog_periodic();
#ifdef UART0_LF_TO_CRLF
	if(c == '\n')
	{
		USART_Tx(UART0, '\r');
	}
#endif

	USART_Tx(UART0, c);

#ifdef UART0_LF_TO_CRLF
	if(c == '\r')
	{
		USART_Tx(UART0, '\n');
	}
#endif
}

unsigned int uart0_send_bytes(const unsigned char *seq, unsigned int len) {
	/* TODO : Use DMA Here ... */

	int i = 0;
	for (i = 0; i < len; i++) {
		uart0_writeb(seq[i]);
	}
	return len;
}

void uart0_drain(void) {
	while (!(UART0->STATUS & UART_STATUS_TXBL))
		;
}

void uart0_init(unsigned long baudrate) {
	USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
	/* Configure controller */

	// Enable clocks
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_UART0, true);

	init.enable = usartDisable;
	init.baudrate = baudrate;
	USART_InitAsync(UART0, &init);

	/* Enable pins at UART0 location */
	UART0->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_TXPEN
			| (UART0_LOCATION << _UART_ROUTE_LOCATION_SHIFT);

	/* Clear previous RX interrupts */
	USART_IntClear(UART0, UART_IF_RXDATAV);
	NVIC_ClearPendingIRQ(UART0_RX_IRQn);

	/* Enable RX interrupts */
	USART_IntEnable(UART0, UART_IF_RXDATAV);
	NVIC_EnableIRQ(UART0_RX_IRQn);

	/* Finally enable it */
	USART_Enable(UART0, usartEnable);
}
