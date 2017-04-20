#include "lib/sensors.h"
#include "dev/radio-sensor.h"
#include "net/packetbuf.h"

#define DBM_VALUE(x)			(-120.0 + ((float)((x) - 20)) / 2)

static int radio_is_initialized = 0;
static int radio_is_active = 0;

static void init(void) {
	radio_is_initialized = 1;
	radio_is_active = 1;
}

static void activate(void) {
	if (!radio_is_initialized) {
		init();
	}
	radio_is_active = 1;
}

static void deactivate(void) {
	radio_is_active = 0;
}

static int active(void) {
	return radio_is_active;
}

static int value(int type) {
	int32_t radio_sensor;
	float radio_sensor_value;

	switch (type) {
	case RADIO_SENSOR_LAST_PACKET:
	case RADIO_SENSOR_LAST_VALUE:
	default:
		radio_sensor_value = DBM_VALUE(packetbuf_attr(PACKETBUF_ATTR_RSSI));
		radio_sensor = (int32_t)(radio_sensor_value * 10);
	}

	return radio_sensor;
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

SENSORS_SENSOR(radio_sensor, RADIO_SENSOR, value, configure, status);
