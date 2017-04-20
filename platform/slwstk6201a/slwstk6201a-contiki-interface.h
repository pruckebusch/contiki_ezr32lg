#ifndef PLATFORM_SLWSTK6201A_SLWSTK6201A_CONTIKI_INTERFACE_H_
#define PLATFORM_SLWSTK6201A_SLWSTK6201A_CONTIKI_INTERFACE_H_

#include "contiki.h"
#include "contiki-net.h"
#include "sys/autostart.h"
#include "sys/node-id.h"
#include "dev/leds.h"
#include "dev/serial-line.h"
#include "dev/slip.h"
#include "dev/watchdog.h"
#include "dev/xmem.h"
#include "lib/random.h"

#include "net/netstack.h"
#include "net/uip.h"
#include "net/rime.h"
#include "net/mac/frame802154.h"

#if WITH_UIP6
#include "net/ipv6/uip-ds6.h"
#endif

#include "lib/sensors.h"
#include "dev/button-sensor.h"
#include "dev/battery-sensor.h"
#include "dev/radio-sensor.h"

// Platform
#include "battery-sensor.h"
#include "button0-sensor.h"
#include "button1-sensor.h"
#include "net/radio-arch.h"
#include "dev/flash.h"

#endif
