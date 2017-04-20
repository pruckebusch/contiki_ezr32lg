#include <string.h>
#include "sys/node-id.h"
#include "contiki-conf.h"
#include "em_system.h"

unsigned short node_id = 0;
unsigned char node_mac[8];

void node_id_restore(void) {
	(*(uint32_t *) node_mac) = DEVINFO->UNIQUEL;
	(*(((uint32_t *) node_mac) + 1)) = DEVINFO->UNIQUEH;

	node_id = (unsigned short) SYSTEM_GetUnique();
}

void node_id_burn(unsigned short id) {
	// not supported
}
