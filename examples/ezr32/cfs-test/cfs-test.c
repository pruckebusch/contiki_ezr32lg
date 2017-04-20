#include <stdio.h>
#include "contiki.h"
#include "cfs/cfs.h"
#include "cfs/cfs-coffee.h"
#include <string.h>

PROCESS(example_coffee_process, "Coffee example");
AUTOSTART_PROCESSES(&example_coffee_process);
#define FILENAME 		"test"
#define DATA_LENGTH		1024

/* Formatting is needed if the storage device is in an unknown state;
   e.g., when using Coffee on the storage device for the first time. */
#ifndef NEED_FORMATTING
#define NEED_FORMATTING 0
#endif

// #define MEM_SIZE						16384
// const uint32_t mem_space[MEM_SIZE]		= {0};

static int
file_test(const char *filename, char *msg)
{
	// printf("\n\nMemory location mem_space[0]: %02X, memory location mem_space[16383]: %02X \n", &mem_space[0], &mem_space[16383]);
	uint32_t data[4096] = {0};
	int fd;
	int r;
	char message[32];
	char buf[64];
	strncpy(message, "First Message", sizeof(message) - 1);
	message[sizeof(message) - 1] = '\0';
	strcpy(buf,message);
	/*First message is to test if the write will succeed*/
	printf("Write Test: Will write \"%s\" to file \"%s\"\n",buf,FILENAME);

  /* Obtain a file descriptor for the file, capable of handling both
     reads and writes. */
	fd = cfs_open(FILENAME, CFS_WRITE | CFS_APPEND | CFS_READ);
	if(fd < 0) {
		printf("failed to open %s\n", FILENAME);
		return 0;
	}
  /*Write message to Filesystem*/
	r = cfs_write(fd, data, (sizeof(data) / sizeof(data[0])));
	if(r != (sizeof(data) / sizeof(data[0]))) {
		printf("failed to write %d bytes to %s\n",
				(int)sizeof(message), FILENAME);
		cfs_close(fd);
		return 0;
	}
	cfs_close(fd);
	printf("Write Test: Successfully wrote data to \"%s\" wrote %d bytes\n " ,FILENAME, r);

	strcpy(buf,"fail");
	fd = cfs_open(FILENAME, CFS_READ);
	if(fd < 0) {
		printf("failed to open %s\n", FILENAME);
		return 0;
	}
	r = cfs_read(fd, buf, (sizeof(data) / sizeof(data[0])));
	if(r != (sizeof(data) / sizeof(data[0]))) {
		printf("failed to write %d bytes to %s\n",(int)sizeof(message), FILENAME);
		cfs_close(fd);
		return 0;
	}
      /* compare with the original message to see if the message was read
      correctly, if it reads fail then it will print fail*/
	printf("Read Test: Read \"%s\" from \"%s\"\n",buf, FILENAME);
	cfs_close(fd);
     /*Append test */
	strcpy(data,"Append Something");
	fd = cfs_open(FILENAME, CFS_WRITE | CFS_APPEND | CFS_READ);
	if(fd < 0) {
		printf("failed to open %s\n", FILENAME);
		return 0;
	}
	r = cfs_write(fd, data, (sizeof(data) / sizeof(data[0])));
	cfs_close(fd);
	printf("Append Test: Successfully data to \"%s\" \n ",FILENAME);
	strcpy(buf,"fail");
	fd = cfs_open(FILENAME, CFS_READ);
	if(fd < 0) {
		printf("failed to open %s\n", FILENAME);
		return 0;
	}
	cfs_read(fd,buf,(sizeof(data) / sizeof(data[0])));
	printf("Read First Part \"%s\"\n",buf);
       /*seek test*/
	if(cfs_seek(fd, (sizeof(data) / sizeof(data[0])), CFS_SEEK_SET) == -1) {
		printf("seek failed\n");
		cfs_close(fd);
		return 0;
	}
  //cfs_seek(fd, sizeof(message), CFS_SEEK_SET);
    /*if the seek fails then the second message will not
    be the same as the last message write to the file*/
	cfs_read(fd,buf,(sizeof(data) / sizeof(data[0])));
	printf("Read Second Part: \"%s\"\n",buf);
	cfs_close(fd);
  /* Release the internal resources held by Coffee for
     the file descriptor. */
	cfs_remove(FILENAME);
	fd = cfs_open(FILENAME, CFS_READ);
	if(fd != -1) {
		printf("ERROR: could read from memory\n");
		return 0;
	}
	printf("Successfully removed file\n");
	return 1;
}

const uint8_t data_arr[DATA_LENGTH] = { 71, 101, 110, 101, 114, 97, 116, 101, 100, 32, 98, 121, 32, 69, 65, 71, 76, 69, 32, 67, 65, 77, 32, 80, 114, 111, 99, 101, 115, 115, 111, 114, 32, 56, 46, 49, 46, 48, 10, 10, 68, 114, 105, 108, 108, 32, 83, 116, 97, 116, 105, 111, 110, 32, 73, 110, 102, 111, 32, 70, 105, 108, 101, 58, 32, 47, 104, 111, 109, 101, 47, 98, 97, 114, 116, 47, 68, 114, 111, 112, 98, 111, 120, 47, 66, 97, 103, 97, 97, 114, 47, 66, 71, 82, 32, 71, 70, 79, 82, 67, 69, 32, 86, 49, 46, 49, 47, 98, 103, 114, 95, 103, 102, 111, 114, 99, 101, 95, 118, 49, 46, 49, 95, 101, 102, 109, 51, 50, 108, 103, 51, 51, 50, 46, 100, 114, 105, 10, 10, 32, 68, 97, 116, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 54, 47, 48, 52, 47, 50, 48, 49, 55, 32, 49, 52, 58, 53, 53, 10, 32, 68, 114, 105, 108, 108, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 10, 32, 68, 101, 118, 105, 99, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 69, 120, 99, 101, 108, 108, 111, 110, 32, 100, 114, 105, 108, 108, 32, 115, 116, 97, 116, 105, 111, 110, 44, 32, 99, 111, 111, 114, 100, 105, 110, 97, 116, 101, 32, 102, 111, 114, 109, 97, 116, 32, 50, 46, 53, 32, 105, 110, 99, 104, 10, 10, 80, 97, 114, 97, 109, 101, 116, 101, 114, 32, 115, 101, 116, 116, 105, 110, 103, 115, 58, 10, 10, 32, 84, 111, 108, 101, 114, 97, 110, 99, 101, 32, 68, 114, 105, 108, 108, 32, 43, 32, 58, 32, 32, 48, 46, 48, 48, 32, 37, 10, 32, 84, 111, 108, 101, 114, 97, 110, 99, 101, 32, 68, 114, 105, 108, 108, 32, 45, 32, 58, 32, 32, 48, 46, 48, 48, 32, 37, 10, 32, 82, 111, 116, 97, 116, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 110, 111, 10, 32, 77, 105, 114, 114, 111, 114, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 110, 111, 10, 32, 79, 112, 116, 105, 109, 105, 122, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 121, 101, 115, 10, 32, 65, 117, 116, 111, 32, 102, 105, 116, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 121, 101, 115, 10, 32, 79, 102, 102, 115, 101, 116, 88, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 105, 110, 99, 104, 10, 32, 79, 102, 102, 115, 101, 116, 89, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 48, 105, 110, 99, 104, 10, 32, 76, 97, 121, 101, 114, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 68, 114, 105, 108, 108, 115, 32, 72, 111, 108, 101, 115, 10, 10, 68, 114, 105, 108, 108, 32, 70, 105, 108, 101, 32, 73, 110, 102, 111, 58, 10, 10, 32, 68, 97, 116, 97, 32, 77, 111, 100, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 65, 98, 115, 111, 108, 117, 116, 101, 10, 32, 85, 110, 105, 116, 115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 58, 32, 49, 47, 49, 48, 48, 48, 48, 48, 32, 73, 110, 99, 104, 10, 10, 68, 114, 105, 108, 108, 115, 32, 117, 115, 101, 100, 58, 10, 10, 32, 67, 111, 100, 101, 32, 32, 83, 105, 122, 101, 32, 32, 32, 32, 32, 32, 32, 117, 115, 101, 100, 10, 10, 32, 84, 48, 49, 32, 32, 32, 48, 46, 48, 49, 57, 55, 105, 110, 99, 104, 32, 32, 32, 32, 56, 48, 10, 32, 84, 48, 50, 32, 32, 32, 48, 46, 48, 50, 51, 54, 105, 110, 99, 104, 32, 32, 32, 49, 51, 50, 10, 32, 84, 48, 51, 32, 32, 32, 48, 46, 48, 50, 55, 54, 105, 110, 99, 104, 32, 32, 32, 32, 32, 50, 10, 32, 84, 48, 52, 32, 32, 32, 48, 46, 48, 51, 57, 48, 105, 110, 99, 104, 32, 32, 32, 32, 32, 51, 10, 32, 84, 48, 53, 32, 32, 32, 48, 46, 48, 52, 48, 48, 105, 110, 99, 104, 32, 32, 32, 32, 51, 50, 10, 32, 84, 48, 54, 32, 32, 32, 48, 46, 48, 53, 57, 49, 105, 110, 99, 104, 32, 32, 32, 32, 32, 50, 10, 32, 84, 48, 55, 32, 32, 32, 48, 46, 48, 57, 51, 53, 105, 110, 99, 104, 32, 32, 32, 32, 32, 52, 10, 32, 84, 48, 56, 32, 32, 32, 48, 46, 49, 50, 54, 48, 105, 110, 99, 104, 32, 32, 32, 32, 32, 52, 10, 10, 84, 111, 116, 97, 108, 32, 110, 117, 109, 98, 101, 114, 32, 111, 102, 32, 100, 114, 105, 108, 108, 115, 58, 32, 50, 53, 57, 10, 10, 80, 108, 111, 116, 102, 105, 108, 101, 115, 58, 10, 10, 32, 47, 104, 111, 109, 101, 47, 98, 97, 114, 116, 47, 68, 114, 111, 112, 98, 111, 120, 47, 66, 97, 103, 97, 97, 114, 47, 66, 71, 82, 32, 71, 70, 79, 82, 67, 69, 32, 86, 49, 46, 49, 47, 98, 103, 114, 95, 103, 102, 111, 114, 99, 101, 95, 118, 49, 46, 49, 95, 101, 102, 109, 51, 50, 108, 103, 51, 51, 50, 46, 84, 88, 84, 10, 0, 71, 101, 110, 101, 114, 97, 116, 101, 100, 32, 98, 121, 32, 69, 65, 71, 76, 69, 32, 67, 65, 77, 32, 80, 114, 111, 99, 101, 115, 115, 111, 114, 32, 56, 46, 49, 46, 48, 10, 10, 80, 104, 111, 116, 111, 112};

static int data_test(const char* filename) {
	int fd;
	int r;
	uint8_t buf[DATA_LENGTH];

	// first message is to test if the write will succeed
	printf("Will write %d bytes to file \"%s\"\n", DATA_LENGTH, filename);

	// obtain a file descriptor for the file, capable of handling both reads and writes.
	fd = cfs_open(filename, CFS_WRITE | CFS_APPEND | CFS_READ);
	if (fd < 0) {
		printf("failed to open %s\n", filename);
		return 0;
	}

	// write message to the filesystem
	r = cfs_write(fd, data_arr, (sizeof(data_arr) / sizeof(data_arr[0])));
	if (r != (sizeof(data_arr) / sizeof(data_arr[0]))) {
		printf("failed to write %d bytes to %s\n", (int) sizeof(data_arr), filename);
		cfs_close(fd);
		return 0;
	}

	cfs_close(fd);
	printf("Write Test: Successfully wrote data to \"%s\" wrote %d bytes\n ", filename, r);


	int fd2;
	fd2 = cfs_open(filename, CFS_READ);
	if (fd2 < 0) {
		printf("failed to open %s\n", filename);
		return 0;
	}

	r = cfs_read(fd2, buf, (sizeof(data_arr) / sizeof(data_arr[0])));
	if (r != (sizeof(data_arr) / sizeof(data_arr[0]))) {
		printf("failed to write %d bytes to %s\n", (int) sizeof(data_arr), filename);
		cfs_close(fd2);
		return 0;
	}

	int i;
	for (i = 0; i < DATA_LENGTH; i++) {
		printf("%d, ", buf[i]);
	}

	cfs_close(fd2);
}

PROCESS_THREAD(example_coffee_process, ev, data)
{
  PROCESS_BEGIN();

#if NEED_FORMATTING
  cfs_coffee_format();
#endif

  /* Ensure that we will be working with a new file. */
  cfs_remove("data_test");

  /*if(file_test(FILENAME, "The first test") == 0) {
    printf("file test 1 failed\n");
  }*/

	if (data_test("data_test") == 0) {
		printf("file test 1 failed\n");
	} else {
		printf("test succeed\n");
	}

  PROCESS_END();
}
