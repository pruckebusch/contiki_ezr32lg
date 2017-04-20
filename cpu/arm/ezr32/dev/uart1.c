#include "uart1.h"

static int (*uart1_input_handler)(unsigned char c);

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

//UART1_TX_IRQHandler
void UART1_RX_IRQHandler(void)
{
  unsigned char c;

  ENERGEST_ON(ENERGEST_TYPE_IRQ);

  if(UART1->STATUS & UART_STATUS_RXDATAV)
  {
    c = USART_Rx(UART1);
    if(uart1_input_handler != NULL) uart1_input_handler(c);
  }
  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}

void uart1_init(unsigned long baudrate) {
	/* Enable peripheral clocks */
	CMU_ClockEnable(cmuClock_HFPER, true);
	/* Configure GPIO pins */
	CMU_ClockEnable(cmuClock_GPIO, true);
	/* To avoid false start, configure output as high */
	GPIO_PinModeSet(RETARGET_TXPORT, RETARGET_TXPIN, gpioModePushPull, 1);
	GPIO_PinModeSet(RETARGET_RXPORT, RETARGET_RXPIN, gpioModeInput, 0);

	USART_InitAsync_TypeDef init = { usartEnable, /* Enable RX/TX when init completed. */
	0, /* Use current configured reference clock for configuring baudrate. */
	baudrate,
	usartOVS16, /* 16x oversampling. */
	usartDatabits8, /* 8 databits. */
	usartNoParity, /* No parity. */
	usartStopbits1, /* 1 stopbit. */
	false, /* Do not disable majority vote. */
	false, /* Not USART PRS input mode. */
	usartPrsRxCh0 /* PRS channel 0. */
	}

	/* Enable DK RS232/UART switch */
	RETARGET_PERIPHERAL_ENABLE();

	CMU_ClockEnable(RETARGET_CLK, true);

	/* Configure USART for basic async operation */
	init.enable = usartDisable;
	USART_InitAsync(RETARGET_UART, &init);

	/* Enable pins at correct UART/USART location. */
	RETARGET_UART->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | RETARGET_LOCATION;

	/* Clear previous RX interrupts */
	USART_IntClear(RETARGET_UART, USART_IF_RXDATAV);
	NVIC_ClearPendingIRQ(RETARGET_IRQn);

	/* Enable RX interrupts */
	USART_IntEnable(RETARGET_UART, USART_IF_RXDATAV);
	NVIC_EnableIRQ(RETARGET_IRQn);

	/* Finally enable it */
	USART_Enable(RETARGET_UART, usartEnable);
}

void uart1_drain(void) {
	while (!(UART1->STATUS & UART_STATUS_TXBL))
		;
}

unsigned int uart1_send_bytes(const unsigned char *seq, unsigned int len) {
	/* TODO : Use DMA Here ... */

	int i = 0;
	for (i = 0; i < len; i++) {
		uart1_writeb(seq[i]);
	}
	return len;
}

void uart1_writeb(unsigned char c) {
	watchdog_periodic();
#ifdef UART1_LF_TO_CRLF
	if (c == '\n') {
		USART_Tx(RETARGET_UART, '\r');
	}
#endif

	USART_Tx(RETARGET_UART, c);

#ifdef UART1_LF_TO_CRLF
	if (c == '\r') {
		USART_Tx(RETARGET_UART, '\n');
	}
#endif
}

uint8_t uart1_active(void) {
	return 0;
}

void uart1_set_input(int (*input)(unsigned char c)) {
	uart1_input_handler = input;
}

int *uart1_get_input(void) {
	return (int*) uart1_input_handler;
}
