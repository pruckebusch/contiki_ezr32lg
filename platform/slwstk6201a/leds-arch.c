#include "contiki-conf.h"
#include "platform-conf.h"
#include "dev/leds.h"
#include "gpio.h"

void leds_arch_init(void) {
	GPIO_PinModeSet(PORT_LED1, PORT_PIN_LED1, gpioModePushPull, 0);
	GPIO_PinModeSet(PORT_LED2, PORT_PIN_LED2, gpioModePushPull, 0);
}

unsigned char leds_arch_get(void) {
	unsigned char ret = 0;

	if (gpio_get_value(GPIO_USER_LED1))
		ret |= LEDS_USER1;
	if (gpio_get_value(GPIO_USER_LED2))
		ret |= LEDS_USER2;

	return ret;
}

void leds_arch_set(unsigned char leds) {
	// Set Pin to low level to turn Led ON
	if (leds & LEDS_USER1)
        gpio_set_value(GPIO_USER_LED1, 1);
	else
		gpio_set_value(GPIO_USER_LED1, 0);

	if (leds & LEDS_USER2)
		gpio_set_value(GPIO_USER_LED2, 1);
	else
		gpio_set_value(GPIO_USER_LED2, 0);
}

