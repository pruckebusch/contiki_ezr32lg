#ifndef INC_UART1_H_
#define INC_UART1_H_


#include "contiki.h"
#include <stdlib.h>
#include "stddef.h"
#include "sys/energest.h"
#include "em_device.h"
#include "uart1.h"
#include "dev/watchdog.h"

#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"

#define RETARGET_IRQ_NAME    	USART1_RX_IRQHandler         /* USART IRQ Handler */
#define RETARGET_CLK         	cmuClock_USART1              /* HFPER Clock */
#define RETARGET_IRQn        	USART1_RX_IRQn               /* IRQ number */
#define RETARGET_UART        	USART1                       /* UART instance */
#define RETARGET_TX          	USART_Tx                     /* Set TX to USART_Tx */
#define RETARGET_RX          	USART_Rx                     /* Set RX to USART_Rx */
#define RETARGET_LOCATION    	USART_ROUTE_LOCATION_LOC2    /* Location of of the USART I/O pins */
#define RETARGET_TXPORT      	gpioPortD                    /* USART transmission port */
#define RETARGET_TXPIN       	7                            /* USART transmission pin */
#define RETARGET_RXPORT      	gpioPortD                    /* USART reception port */
#define RETARGET_RXPIN       	6                            /* USART reception pin */
#define RETARGET_USART       	1                            /* Includes em_usart.h */
#define RETARGET_PERIPHERAL_ENABLE()

#define UART1_LF_TO_CRLF 		1

void uart1_init(uint32_t baudrate);
void uart1_drain(void);
unsigned int uart1_send_bytes(const unsigned char *seq, unsigned int len);
void uart1_writeb(unsigned char c);

uint8_t uart1_active(void);
void uart1_set_input(int (*input)(unsigned char c));
int *uart1_get_input(void);

#endif
