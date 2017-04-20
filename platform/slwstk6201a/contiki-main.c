#include "slwstk6201a-contiki-interface.h"

// ToDo
// Transfer all includes to slwstk6201a-contiki-interface.h

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/process.h>
#include <sys/procinit.h>
#include <sys/energest.h>
#include <sys/rtimer.h>
#include <clock.h>
#include <etimer.h>

#include <rimeaddr.h>

#include "core_cm3.h"

#include "platform-conf.h"
#include "em_cmu.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "platform-init.h"

#include "power.h"
#include "uart1.h"
#include "dmactrl.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

// sensors to include
SENSORS(&button0_sensor, &battery_sensor, &button1_sensor, &radio_sensor);

// local variables
unsigned char node_mac[8];
rimeaddr_t n_addr;
static uip_ipaddr_t ipaddr;
unsigned short node_id;
unsigned int idle_count = 0;

// static main loop functions
// used for initialization & debugging information
static void print_processes(struct process * const processes[]);
static void print_device_config(void);
static void set_rime_addr(void);

/*--------------------------------------------------------------------------*/
void HardFault_Handler(void) {
	while (1)
		;
}

void MemManage_Handler(void) {
	while (1)
		;
}

void BusFault_Handler(void) {
	while (1)
		;
}
void UsageFault_Handler(void) {
	while (1)
		;
}

volatile uint32_t *reg;

int main(void) {
	rimeaddr_t addr;
	uint64_t uuid;

	uint32_t u32_fullresetcause, u32_resetcause;

	CHIP_Init();

	gpio_init();
	leds_init();

    leds_off(LEDS_ALL);

#ifdef DEBUGUART_USART0
	usart0_init(115200);
	usart0_set_input(serial_line_input_byte);
#elif DEBUGUART_LEUART1
	leuart1_init(9600);
	leuart1_set_input(serial_line_input_byte);
#elif DEBUGUART_UART0
	uart0_init(115200);
	uart0_set_input(serial_line_input_byte);
#elif DEBUGUART_UART1
	uart1_init(115200);
	uart1_set_input(serial_line_input_byte);
#else
#warning "No Debug UART configured"
#endif

	// clear screen command
	PRINTF("\e[1;1H\e[2J");
	PRINTF("\r\nWelcome to EZR32 Leopard Gecko \r\n");

	CMU_HFRCOBandSet(HFRCOBAND_VALUE);

	// Get Full Reset Cause as soon as possible
	u32_fullresetcause = RMU->RSTCAUSE;
	u32_resetcause = RMU_ResetCauseGet();

	// Get Main reset cause and clear it for next
	RMU_ResetCauseClear();

	power_init();

	setupSWO();

	burtc_crystal_init(u32_fullresetcause);

	_gpio_config();

	adc_init();
	dma_init();

	uuid = SYSTEM_GetUnique();
	flash_init();

#ifndef NO_RTIMER
	// Process Init
	rtimer_init();
#endif
	process_init();
	/* Initialize Contiki */
	PRINTF("Initializing Contiki... ");
	fflush(stdout);

	clock_init();
	watchdog_init();
	process_init();
	process_start(&etimer_process, NULL);
	ctimer_init();
	serial_line_init();
	process_start(&sensors_process, NULL);

	PRINTF("Done!\n");


	// initialize networking
	PRINTF("Initializing network... ");
	fflush(stdout);

	// restore node id if such has been stored in external mem
#ifdef NODEID
	node_id = NODEID;
#else
	// configure node_id & mac
	node_id_restore();
#endif

	set_rime_addr();
	random_init(node_id);
	netstack_init();

#if UIP_CONF_IPV6
	memcpy(&uip_lladdr.addr, node_mac, sizeof(uip_lladdr.addr));
	queuebuf_init();
	process_start(&tcpip_process, NULL);
	uip_ipaddr_t ipaddr;
	uip_ip6addr(&ipaddr, 0xfc00, 0, 0, 0, 0, 0, 0, 0);
	uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
	uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
#endif

	PRINTF("Done!\n");

	PRINTF("Formatting the storage area assigned to Coffee... ");
	if(cfs_coffee_format() == -1) {
		PRINTF("\nFailed formatting the storage area!\n");
	} else {
		PRINTF("Done! \n");
	}
	energest_init();
	ENERGEST_ON(ENERGEST_TYPE_CPU);

	/* Start user processes */
	print_device_config();
	PRINTF("\n--- RUNNING %s ON EZR32 Leopard Gecko --- \n\n", CONTIKI_VERSION_STRING);
	print_processes(autostart_processes);
	autostart_start(autostart_processes);

	// start the process scheduler loop
	watchdog_start();
	while (1) {

		int r;
		do {
			// reset wdog
			watchdog_periodic();
			r = process_run();
		} while (r > 0);

		// ToDo
		// avoid LPM when a device is connected to serial I/O
		// ZIE PORTING CONTIKI TO NEW HW PLATFORMS: CPU FOLDER
		/*
		if (process_nevents() == 0 && !Virtual_ComPort_IsOpen()) {
			ENERGEST_OFF(ENERGEST_TYPE_CPU);
			ENERGEST_ON(ENERGEST_TYPE_LPM);
			watchdog_stop();
			lpm_enter_stopmode();			// Enter LPM: Stop mode with RTC
			watchdog_start();
			ENERGEST_OFF(ENERGEST_TYPE_LPM);
			ENERGEST_ON(ENERGEST_TYPE_CPU);
		}*/
	}

	return 0;
}

static void print_processes(struct process * const processes[]) {
	/* const struct process * const * p = processes; */
	PRINTF("Starting");
	while (*processes != NULL) {
		PRINTF(" '%s'", (*processes)->name);
		processes++;
	}
	PRINTF("\n");
}

static void print_device_config(void) {
	int i;
	PRINTF("RIME ");
	for (i = 0; i < sizeof(n_addr.u8) - 1; i++) {
		PRINTF("%d.", n_addr.u8[i]);
	}
	PRINTF("%d\n", n_addr.u8[i]);

	if (node_id) {
		PRINTF("node id %u\n", node_id);
	} else {
		PRINTF("\n \n NODE ID NOT SET \n");
	}

	PRINTF("%s, %s, radio frequency %iMHz\n",
	NETSTACK_MAC.name, NETSTACK_RDC.name, RF_FREQUENCY / 1000000);

#if UIP_CONF_IPV6
	PRINTF("Tentative link-local IPv6 address ");
	{
		uip_ds6_addr_t *lladdr;
		int i;
		lladdr = uip_ds6_get_link_local(-1);
		for(i = 0; i < 7; ++i) {
			PRINTF("%02x%02x:", lladdr->ipaddr.u8[i * 2],
					lladdr->ipaddr.u8[i * 2 + 1]);
		}
		PRINTF("%02x%02x\r\n", lladdr->ipaddr.u8[14], lladdr->ipaddr.u8[15]);
	}
#endif // UIP_CONF_IPV6
}

static void set_rime_addr(void) {
	int i;

	memset(&n_addr, 0, sizeof(rimeaddr_t));

	// Set node address
#if UIP_CONF_IPV6
	n_addr.u8[7] = node_id & 0xff;
	n_addr.u8[6] = node_id >> 8;
#else
	n_addr.u8[0] = node_id & 0xff;
	n_addr.u8[1] = node_id >> 8;
#endif

	rimeaddr_set_node_addr(&n_addr);
}
