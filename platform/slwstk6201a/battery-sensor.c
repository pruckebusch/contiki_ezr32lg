#include "adc.h"
#include "battery-sensor.h"
#include "slwstk6201a-contiki-interface.h"

static int is_active = 0;

static void init(void) {
	is_active = 1;
}

static void activate_batt_sens(void) {
	is_active = 1;
}

static void deactivate_batt_sens(void) {
	is_active = 0;
}

static int batt_sens_is_active(void) {
	return is_active;
}

static uint32_t value(int type) {
	// ToDo
	// convert to float
	return adc_get_battery();
}

static int configure(int type, int value) {
	switch (type) {
	case SENSORS_HW_INIT:
		init();
		return 1;
	case SENSORS_ACTIVE:
		if (value) {
			activate_batt_sens();
		} else {
			deactivate_batt_sens();
		}
		return 1;
	}

	return 0;
}

static int status(int type) {
	switch (type) {
	case SENSORS_READY:
		return batt_sens_is_active();
	}

	return 0;
}

SENSORS_SENSOR(battery_sensor, BATTERY_SENSOR, value, configure, status);
