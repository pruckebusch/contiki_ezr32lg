#include <stdio.h>
#include <time.h>

#include "contiki.h"
#include "cfs/cfs.h"
#include "cfs/cfs-coffee.h"
#include "platform-conf.h"
#include "net/netstack.h"
#include "lib/sensors.h"
#include "battery-sensor.h"
#include "dev/button-sensor.h"
#include "dev/radio-sensor.h"
#include "dev/leds.h"
#include "slwstk6201a-contiki-interface.h"
#include "radio-arch.h"

#define HEADER_SIZE		5
#define MESSAGE_SIZE	60
// #define DATA_LENGTH		1024
#define DATA_LENGTH		128
#define PAYLOAD_SIZE	(MESSAGE_SIZE - HEADER_SIZE)
#define FILENAME 		"test"

#define PORT			128

int32_t fixed_mul_16(int32_t x, int32_t y) {
	return ((int64_t) x * (int64_t) y) / (1 << 16);
}

int32_t fixed_div_16(int32_t x, int32_t y) {
	return ((int64_t) x * (1 << 16)) / y;
}

PROCESS(radiotest_process, "Radio Test");
AUTOSTART_PROCESSES(&radiotest_process);

// 1024 bytes array (1*1024)
// packetbuf uses uint8 only
// const uint8_t data_arr[DATA_LENGTH] = { 71, 101, 110, 101, 114, 97, 116, 101, 100, 32, 98, 121, 32, 69, 65, 71, 76, 69, 32, 67, 65, 77, 32, 80, 114, 111, 99, 101, 115, 115, 111, 114, 32, 56, 46, 49, 46, 48, 10, 10, 68, 114, 105, 108, 108, 32, 83, 116, 97, 116, 105, 111, 110, 32, 73, 110, 102, 111, 32, 70, 105, 108, 101, 58, 32, 47, 104, 111, 109, 101, 47, 98, 97, 114, 116, 47, 68, 114, 111, 112, 98, 111, 120, 47, 66, 97, 103, 97, 97, 114, 47, 66, 71, 82, 32, 71, 70, 79, 82, 67, 69, 32, 86, 49, 46, 49, 47, 98, 103, 114, 95, 103, 102, 111, 114, 99, 101, 95, 118, 49, 46, 49, 95, 101, 102, 109, 51, 50, 108, 103, 51, 51, 50, 46, 100, 114, 105, 10, 10, 32, 68, 97, 116, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 54, 47, 48, 52, 47, 50, 48, 49, 55, 32, 49, 52, 58, 53, 53, 10, 32, 68, 114, 105, 108, 108, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 10, 32, 68, 101, 118, 105, 99, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 69, 120, 99, 101, 108, 108, 111, 110, 32, 100, 114, 105, 108, 108, 32, 115, 116, 97, 116, 105, 111, 110, 44, 32, 99, 111, 111, 114, 100, 105, 110, 97, 116, 101, 32, 102, 111, 114, 109, 97, 116, 32, 50, 46, 53, 32, 105, 110, 99, 104, 10, 10, 80, 97, 114, 97, 109, 101, 116, 101, 114, 32, 115, 101, 116, 116, 105, 110, 103, 115, 58, 10, 10, 32, 84, 111, 108, 101, 114, 97, 110, 99, 101, 32, 68, 114, 105, 108, 108, 32, 43, 32, 58, 32, 32, 48, 46, 48, 48, 32, 37, 10, 32, 84, 111, 108, 101, 114, 97, 110, 99, 101, 32, 68, 114, 105, 108, 108, 32, 45, 32, 58, 32, 32, 48, 46, 48, 48, 32, 37, 10, 32, 82, 111, 116, 97, 116, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 110, 111, 10, 32, 77, 105, 114, 114, 111, 114, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 110, 111, 10, 32, 79, 112, 116, 105, 109, 105, 122, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 121, 101, 115, 10, 32, 65, 117, 116, 111, 32, 102, 105, 116, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 121, 101, 115, 10, 32, 79, 102, 102, 115, 101, 116, 88, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 105, 110, 99, 104, 10, 32, 79, 102, 102, 115, 101, 116, 89, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 105, 110, 99, 104, 10, 32, 76, 97, 121, 101, 114, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 68, 114, 105, 108, 108, 115, 32, 72, 111, 108, 101, 115, 10, 10, 68, 114, 105, 108, 108, 32, 70, 105, 108, 101, 32, 73, 110, 102, 111, 58, 10, 10, 32, 68, 97, 116, 97, 32, 77, 111, 100, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 65, 98, 115, 111, 108, 117, 116, 101, 10, 32, 85, 110, 105, 116, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 49, 47, 49, 48, 48, 48, 48, 48, 32, 73, 110, 99, 104, 10, 10, 68, 114, 105, 108, 108, 115, 32, 117, 115, 101, 100, 58, 10, 10, 32, 67, 111, 100, 101, 32, 32, 83, 105, 122, 101, 32, 32, 32, 32, 32, 32, 32, 117, 115, 101, 100, 10, 10, 32, 84, 48, 49, 32, 32, 32, 48, 46, 48, 49, 57, 55, 105, 110, 99, 104, 32, 32, 32, 32, 56, 48, 10, 32, 84, 48, 50, 32, 32, 32, 48, 46, 48, 50, 51, 54, 105, 110, 99, 104, 32, 32, 32, 49, 51, 50, 10, 32, 84, 48, 51, 32, 32, 32, 48, 46, 48, 50, 55, 54, 105, 110, 99, 104, 32, 32, 32, 32, 32, 50, 10, 32, 84, 48, 52, 32, 32, 32, 48, 46, 48, 51, 57, 48, 105, 110, 99, 104, 32, 32, 32, 32, 32, 51, 10, 32, 84, 48, 53, 32, 32, 32, 48, 46, 48, 52, 48, 48, 105, 110, 99, 104, 32, 32, 32, 32, 51, 50, 10, 32, 84, 48, 54, 32, 32, 32, 48, 46, 48, 53, 57, 49, 105, 110, 99, 104, 32, 32, 32, 32, 32, 50, 10, 32, 84, 48, 55, 32, 32, 32, 48, 46, 48, 57, 51, 53, 105, 110, 99, 104, 32, 32, 32, 32, 32, 52, 10, 32, 84, 48, 56, 32, 32, 32, 48, 46, 49, 50, 54, 48, 105, 110, 99, 104, 32, 32, 32, 32, 32, 52, 10, 10, 84, 111, 116, 97, 108, 32, 110, 117, 109, 98, 101, 114, 32, 111, 102, 32, 100, 114, 105, 108, 108, 115, 58, 32, 50, 53, 57, 10, 10, 80, 108, 111, 116, 102, 105, 108, 101, 115, 58, 10, 10, 32, 47, 104, 111, 109, 101, 47, 98, 97, 114, 116, 47, 68, 114, 111, 112, 98, 111, 120, 47, 66, 97, 103, 97, 97, 114, 47, 66, 71, 82, 32, 71, 70, 79, 82, 67, 69, 32, 86, 49, 46, 49, 47, 98, 103, 114, 95, 103, 102, 111, 114, 99, 101, 95, 118, 49, 46, 49, 95, 101, 102, 109, 51, 50, 108, 103, 51, 51, 50, 46, 84, 88, 84, 10, 0, 71, 101, 110, 101, 114, 97, 116, 101, 100, 32, 98, 121, 32, 69, 65, 71, 76, 69, 32, 67, 65, 77, 32, 80, 114, 111, 99, 101, 115, 115, 111, 114, 32, 56, 46, 49, 46, 48, 10, 10, 80, 104, 111, 116, 111, 112};
const uint8_t data_arr[DATA_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
static uint8_t recv_valid[DATA_LENGTH] = {0};
uint8_t recv_data[MESSAGE_SIZE] = {0};
// initialize, will get garbage collected otherwise
uint16_t packet_len = 0;
uint16_t rcv_packet_len = 0;
uint16_t counter = 0;

static void abc_recv(struct abc_conn *c) {
	// packet received
	/*if (packetbuf_datalen() < PACKET_SIZE
			|| strncmp((char *) packetbuf_dataptr(), HEADER, sizeof(HEADER))) {
		printf("INVALID MESSAGE \n");
	}*/

    uint8_t *datar;
	datar = packetbuf_dataptr();

	leds_toggle(LEDS_USER1);

	uint8_t len_high = ((uint8_t * )datar)[0];
	uint8_t len_low = ((uint8_t * )datar)[1];
	uint8_t packet_id = ((uint8_t * )datar)[2];
	uint8_t message_id = ((uint8_t * )datar)[3];
	uint8_t message_length = ((uint8_t * )datar)[4];

	rcv_packet_len = ((len_high << 8) | (len_low & 0xFF));

	uint8_t len = (message_length - HEADER_SIZE);

	int i = 0; int j = HEADER_SIZE;
	printf("Writing %d bytes of data to recv_data array \n", len);
	for(i = 0; i < len; i++) {
		recv_data[i] = ((uint8_t * )datar)[j];
		printf("%d, ", recv_data[i]);
		j++;
	}

	/*
	for (i = 0; i < (message_length - HEADER_SIZE); i++) {
		printf("%d, ", recv_data[i]);
	}*/

	// printf("\n");

	// The wrong array size messes with the data send to the cfs
	// maybe a wrong file descriptor?

	int fd;
	int r;

	fd = cfs_open(FILENAME, CFS_WRITE | CFS_APPEND);
	if(fd < 0) {
		printf("\nfailed to open %s\n", FILENAME);
	} else {
		r = cfs_write(fd, recv_data, len);
		if(r != len) {
			printf("\nfailed to write %d bytes to %s\n", r, FILENAME);
		}

		cfs_close(fd);

		printf("Successfully wrote data to \"%s\" wrote %d bytes\n " ,FILENAME, r);
	}

	/*
	 * THIS WORKS
	int i = 0; int j = HEADER_SIZE;
	for(i = counter; i < (counter + message_length); i++) {
		recv_valid[i] = ((uint8_t * )datar)[j];
		j++;
	}

	counter += (message_length - HEADER_SIZE);*/

	printf("Received packet length %d, packet_id: %d, message_id: %d, message_length: %d \n", rcv_packet_len, packet_id, message_id, message_length);

	// compare counter and rcv_packet_len to know if last packet is received
	counter += (message_length - HEADER_SIZE);
}
static const struct abc_callbacks abc_call = { abc_recv };
static struct abc_conn abc;

PROCESS_THREAD(radiotest_process, ev, data) {
	PROCESS_BEGIN();

		cfs_remove(FILENAME);

		srand(time(NULL));
		packet_len = (sizeof(data_arr) / sizeof(data_arr[0]));

		SENSORS_ACTIVATE(button1_sensor);
		SENSORS_ACTIVATE(button0_sensor);

		abc_open(&abc, PORT, &abc_call);

	while(1) {
		PROCESS_YIELD();
		if (ev == sensors_event) {
			if(data == &button1_sensor) {
				uint8_t msg_counter = 0;

				// ToDo
				// round to the nearest, upper integer to include the last message (with variable length)
				// divide DATA_LENGTH with PAYLOAD_SIZE and round to ceil
				uint8_t total_msgs = 3;
				// ToDo
				// Multiply decimal part with PAYLOAD SIZE
				// returns the last message size
				uint8_t last_message_size = (18 + HEADER_SIZE);

				printf("Total messages = %d \n", total_msgs);

				// packet_id is same for every message
				uint8_t packet_id = rand() % 255;
				uint8_t packet_len_high = (packet_len >> 8);
				uint8_t packet_len_low = (packet_len & 0xFF);

				uint8_t msg_is_sent = 1;
				do {
					if(msg_is_sent) {
						msg_is_sent = 0;

						uint8_t message_id = msg_counter;
						uint8_t message_length = MESSAGE_SIZE;
						uint8_t buf[MESSAGE_SIZE] = {0};
						uint16_t data_counter = msg_counter * PAYLOAD_SIZE;

						// fill header data
						buf[0] = packet_len_high;
						buf[1] = packet_len_low;
						buf[2] = packet_id;
						buf[3] = message_id;

						if(msg_counter == (total_msgs - 1)) {
							// last packet
							message_length = last_message_size;
						}

						buf[4] = message_length;

						printf("\n\n");

						uint8_t j = 0;
						for (j = HEADER_SIZE; j < message_length; j++) {
							data_counter = (msg_counter * PAYLOAD_SIZE) + (j - HEADER_SIZE);
							buf[j] = data_arr[data_counter];
							printf("%d: %d ", data_counter, data_arr[data_counter]);
						}

						printf("Packet length: %d, packet_id: %d, message_id: %d, message_length: %d \n", ((buf[0] << 8) | buf[1]), buf[2], buf[3], buf[4]);

						packetbuf_copyfrom(buf, MESSAGE_SIZE);
						((uint8_t *)packetbuf_dataptr())[MESSAGE_SIZE] = buf;
						packetbuf_set_datalen(MESSAGE_SIZE);
						msg_is_sent = abc_send(&abc);

						printf("Sent message with id %d \n", buf[3]);

						msg_counter++;
						leds_toggle(LEDS_USER2);
						clock_delay_msec(200);
					}
				} while(msg_counter < total_msgs);

				printf("Sent all data \n");
			}
			if(data == &button0_sensor) {
				printf("Counter: %d \n", counter);
				int i = 0; int fd = 0;
				fd = cfs_open(FILENAME, CFS_READ);
				if (fd < 0) {
					printf("failed to open %s\n", FILENAME);
				} else {
					cfs_read(fd, recv_valid, DATA_LENGTH);

					for(i = 0; i < DATA_LENGTH; i++) {
						printf("%d, ", recv_valid[i]);
					}
				}
			}
		}
	}

	PROCESS_END();
}

