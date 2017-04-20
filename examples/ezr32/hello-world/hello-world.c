#include "contiki.h"
#include "dev/leds.h"

#include <stdio.h> /* For printf() */

static struct etimer et_hw;

PROCESS(hw_prcs, "Hello world process");
AUTOSTART_PROCESSES(&hw_prcs);

PROCESS_THREAD(hw_prcs, ev, data)
{
  PROCESS_BEGIN();

  leds_off(LEDS_ALL);

  while(1) {
      etimer_set(&et_hw, 0.2*CLOCK_SECOND);

      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et_hw));
	  leds_toggle(LEDS_ALL);

	  printf("Hello world! \n");
  }

  PROCESS_END();
}
