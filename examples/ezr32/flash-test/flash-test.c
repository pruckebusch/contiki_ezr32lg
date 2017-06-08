#include "contiki.h"
#include "dev/leds.h"
#include "flash.h"
#include <stdio.h> /* For printf() */

static struct etimer et_hw;

PROCESS(flash_test, "flash test process");
AUTOSTART_PROCESSES(&flash_test);

const uint32_t const flash_text_memory[128] = {0}; 
const uint32_t const data_memory[128] = {	0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
											0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF
										};
uint32_t read_buf[128] = {0};
int i =0;
uint32_t status_page_addr = 0x0FE04000;
uint32_t status_page_val = 0;

uint32_t length = 512;

uint32_t my_text_addr = 0x0001F800;

void printWordInBits(uint32_t* ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=sizeof(int)-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
}

PROCESS_THREAD(flash_test, ev, data)
{
  PROCESS_BEGIN();
  
  etimer_set(&et_hw, 5*CLOCK_SECOND);

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et_hw));
  leds_toggle(LEDS_ALL);
  
  /*
  printf("reading the page lock status\n");
  for(i=0;i<2024;i+=4){
	  printf("0x%08X (w %u): ", base_addr + i, i);
	  printWordInBits((uint32_t*)(base_addr + i));
	  printf("\n");
  }
  
  base_addr = (uint32_t) &data_memory;
  for(i=0;i<128;i+=4){
	  printf("0x%08X (w %u): ", base_addr + i, i);
	  printWordInBits((uint32_t*)(base_addr + i));
	  printf("\n");
  }
  */
  
  flash_erase(my_text_addr,2048);
  
  printf("before %p %p %p 0x%04X\n", (const char *) &data_memory[0], data_memory, flash_text_memory, (uint32_t) flash_text_memory);
  for(i=0;i<length;i+=4){
	  printf("0x%04X ", *(((const char *) &data_memory[0]) + i));
  }
  printf("\n");
  
  for(i=0;i<2048;i+=4){
	  flash_compread(status_page_addr+i, &status_page_val, 4);
	  printWordInBits(&status_page_val);
	  if(i%16==0){
		  printf("\n");
	  }
  }
  printf("\n"); 
  
  length = flash_compwrite(my_text_addr,(const char *) &data_memory[0],length);
  
  printf("AFTER %d\n",length);
  
  leds_toggle(LEDS_ALL);
  
  flash_compread(my_text_addr, &read_buf, 512);
  
  for(i=0;i<128;i++){
	  printf("0x%04X ", read_buf[i]);
  }
  printf("\n");
  
  for(i=0;i<2048;i+=4){
	  flash_compread(status_page_addr+i, &status_page_val, 4);
	  printWordInBits(&status_page_val);
	  if(i%16==0){
		  printf("\n");
	  }
  }
  printf("\n"); 
  leds_toggle(LEDS_ALL);
  
  PROCESS_END();
}
