#ifndef __UART0_H__
#define __UART0_H__

void uart0_set_input(int (*input)(unsigned char c));
int *uart0_get_input(void);

void uart0_writeb(unsigned char c);
unsigned int uart0_send_bytes(const unsigned char *seq, unsigned int len);


void uart0_init(unsigned long baudrate);
uint8_t uart0_active(void);
void uart0_drain(void);

#endif
