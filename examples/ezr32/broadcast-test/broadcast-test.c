#include <stdio.h>
#include "contiki.h"
#include "platform-conf.h"
#include "net/netstack.h"
#include "lib/sensors.h"
#include "battery-sensor.h"
#include "dev/button-sensor.h"
#include "dev/radio-sensor.h"
#include "dev/leds.h"
#include "slwstk6201a-contiki-interface.h"
#include "radio-arch.h"

#define PORT 129

uint8_t tx_buf[]={0x00,0x0F,0x68,0x65,0x6C,0x6C,0x6F,0x68,0x65,0x6C,0x6C,0x6F, 0x68,0x65,0x6C,0x6C,0x6F};
uint8_t buf[256];
uint8_t temp;
int i;

static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from) {
  printf("broadcast message received from %d.%d: '%s'\n",
         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
  leds_toggle(LEDS_USER1);
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

PROCESS(radio_test_process, "Radio test process");

AUTOSTART_PROCESSES(&radio_test_process);

static uint8_t active;

PROCESS_THREAD(radio_test_process, ev, data) {

	PROCESS_BEGIN();

	broadcast_open(&broadcast, PORT, &broadcast_call);

    SENSORS_ACTIVATE(button1_sensor);
    SENSORS_ACTIVATE(button0_sensor);

    while (1) {
		PROCESS_YIELD();

		if (ev == sensors_event) {
			if (data == &button1_sensor) {
			    packetbuf_copyfrom("Hallo Bart, hoe maak je het?", 28);
			    broadcast_send(&broadcast);
			    printf("broadcast message sent\n \n");

				leds_toggle(LEDS_USER2);
			}
		}
    }

    PROCESS_END();
}
