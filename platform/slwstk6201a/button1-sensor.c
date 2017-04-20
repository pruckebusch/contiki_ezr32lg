#include "lib/sensors.h"
#include "dev/button-sensor.h"
#include "platform-conf.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "slwstk6201a-contiki-interface.h"

static int b1_is_initialized = 0;
static int b1_is_active = 0;

static void GPIO_PB2_IRQHandler(void) {
	sensors_changed(&button1_sensor);
}

static void init_b1(void) {
	if (!gpio_is_active()) {
		gpio_init();
	}

	GPIO_PinModeSet(PORT_BTN2, PORT_PIN_BTN2, gpioModeInputPull, 1);
	GPIO_IntConfig(PORT_BTN2, PORT_PIN_BTN2, false, true, true);
	GPIOINT_CallbackRegister(PORT_PIN_BTN2, GPIO_PB2_IRQHandler);
}

static void activate_b1(void) {
	if (!b1_is_initialized) {
		init_b1();
	}
	b1_is_active = 1;
}

static void deactivate_b1(void) {
	b1_is_active = 0;
}

static int is_b1_active(void) {
	return b1_is_active;
}

static int value_b1(int type) {
	return GPIO_IntGet();
}

static int status_b1(int type) {
	switch (type) {
	case SENSORS_ACTIVE:
	case SENSORS_READY:
		return is_b1_active();
	}
	return 0;
}

static int configure_b1(int type, int value) {
	switch (type) {
	case SENSORS_HW_INIT:
		init_b1();
		return 1;
	case SENSORS_ACTIVE:
		if (value_b1) {
			activate_b1();
		} else {
			deactivate_b1();
		}
		return 1;
	}
	return 0;
}

SENSORS_SENSOR(button1_sensor, BUTTON_SENSOR, value_b1, configure_b1, status_b1);
