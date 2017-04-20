#include "lib/sensors.h"
#include "dev/button-sensor.h"
#include "platform-conf.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "slwstk6201a-contiki-interface.h"

static int b0_is_initialized = 0;
static int b0_is_active = 0;

void GPIO_PB1_IRQHandler(void) {
	sensors_changed(&button0_sensor);
}

static void init_b0(void) {
	// check if clocks are enabled
	if (!gpio_is_active()) {
		gpio_init();
	}

	GPIO_PinModeSet(PORT_BTN1, PORT_PIN_BTN1, gpioModeInputPull, 1);
	GPIO_IntConfig(PORT_BTN1, PORT_PIN_BTN1, false, true, true);
	GPIOINT_CallbackRegister(PORT_PIN_BTN1, GPIO_PB1_IRQHandler);
}

static void activate_b0(void) {
	if (!b0_is_initialized) {
		init_b0();
	}
	b0_is_active = 1;
}

static void deactivate_b0(void) {
	b0_is_active = 0;
}

static int is_b0_active(void) {
	return b0_is_active;
}

static int value_b0(int type) {
	return 1;
}

static int status_b0(int type) {
	switch (type) {
	case SENSORS_ACTIVE:
	case SENSORS_READY:
		return is_b0_active();
	}
	return 0;
}

static int configure_b0(int type, int value) {
	switch (type) {
	case SENSORS_HW_INIT:
		init_b0();
		return 1;
	case SENSORS_ACTIVE:
		if (value) {
			activate_b0();
		} else {
			deactivate_b0();
		}
		return 1;
	}
	return 0;
}

SENSORS_SENSOR(button0_sensor, BUTTON_SENSOR, value_b0, configure_b0, status_b0);
