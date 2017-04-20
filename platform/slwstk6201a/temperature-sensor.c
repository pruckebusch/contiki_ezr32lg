#include "temperature-sensor.h"
#include "slwstk6201a-contiki-interface.h"

static int _initialized = 0;
static int _active = 0;

static void init(void) {
	// ToDo
	// Measure temperature
	_initialized = 1;
	_active = 1;
}

static void activate(void) {
	if (!_initialized) {
		init();
	}
	_active = 1;
}

static void deactivate(void) {
	_active = 0;
}

static int active(void) {
	return _active;
}

static int value(int type) {
	return 1;
}

static int configure(int type, int value) {
	switch (type) {
	case SENSORS_HW_INIT:
		init();
		return 1;
	case SENSORS_ACTIVE:
		if (value) {
			activate();
		} else {
			deactivate();
		}
		return 1;
	}

	return 0;
}

static int status(int type) {
	switch (type) {
	case SENSORS_READY:
		return active();
	}

	return 0;
}

SENSORS_SENSOR(temperature_sensor, TEMPERATURE_SENSOR, value, configure, status);
