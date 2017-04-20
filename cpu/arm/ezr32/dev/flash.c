#include "flash.h"

#include <stdio.h>
#include <string.h>

#include "contiki.h"
#include "irq.h"
#include "dmactrl.h"

#include "em_cmu.h"
#include "em_msc.h"
#include "em_dma.h"
#include "em_int.h"
#include "em_emu.h"

#include "system_ezr32lg.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

// KLK-MCH : DOES NOT Work .... still need debugging
//#define FLASH_DMA
#ifdef FLASH_DMA

#define DMA_CHANNEL_WRITEFLASH 0

/* DMA callback structure */
DMA_CB_TypeDef cb;

/* Transfer Flag */
volatile bool transferActive;

static void transferComplete(unsigned int channel, bool primary, void *user);
#endif


/*---------------------------------------------------------------------------*/
void flash_init(void)
{
  MSC_Init();
  // ToDo
  // enable DMA
#ifdef FLASH_DMA
  DMA_Init_TypeDef        dmaInit;
  DMA_CfgChannel_TypeDef  chnlCfg;
  DMA_CfgDescr_TypeDef    descrCfg;

//  CMU_ClockEnable(cmuClock_DMA, true);
  /* Initializing the DMA */
  /*
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;
  DMA_Init(&dmaInit);
*/
  /* Setting call-back function */
  cb.cbFunc  = transferComplete;
  cb.userPtr = NULL;

  /* Setting up channel */
  chnlCfg.highPri   = false;
  chnlCfg.enableInt = true;
  chnlCfg.select    = DMAREQ_MSC_WDATA;
  chnlCfg.cb        = &(cb);
  DMA_CfgChannel(DMA_CHANNEL_WRITEFLASH, &chnlCfg);

  /* Setting up channel descriptor */
  descrCfg.dstInc  = dmaDataIncNone;
  descrCfg.srcInc  = dmaDataInc4;
  descrCfg.size    = dmaDataSize4;
  descrCfg.arbRate = dmaArbitrate1;
  descrCfg.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL_WRITEFLASH, true, &descrCfg);
#endif
}

int flash_write(uint32_t address, uint32_t* data, uint32_t length) {
	PRINTF("Start writing at address 0x%08X \n", address);

	uint32_t wordIndex;
	uint32_t timeOut;
	uint32_t *addr_ptr = (uint32_t*) address;

	/*
	if (SystemCoreClock >= 1000000) {
		wordIndex = 0;
		while (wordIndex < length) {
			MSC->WDATA = *data++;
			wordIndex++;
			MSC->WRITECMD = MSC_WRITECMD_WRITEONCE;
		}
	} else {
		PRINTF("Increment system core clock! \n");
	}

	timeOut = MSC_PROGRAM_TIMEOUT;
	while ((MSC->STATUS & MSC_STATUS_BUSY) && (timeOut != 0)) {
		timeOut--;
	}*/

	if (SystemCoreClock >= 1000000) {
		wordIndex = 0;
		while(wordIndex < length) {
			MSC->ADDRB = addr_ptr;
			MSC->WDATA = *data++;
			wordIndex++;
			MSC->WRITECMD = MSC_WRITECMD_WRITEONCE;
			PRINTF("ADDR PTR: %p DATA: 0x%08X \n", addr_ptr, *data);
			++addr_ptr;
		}
	} else {
		PRINTF("Increment system core clock! \n");
	}

	timeOut = MSC_PROGRAM_TIMEOUT;
	while ((MSC->STATUS & MSC_STATUS_BUSY) && (timeOut != 0)) {
		timeOut--;
	}
	/* Check for timeout */
	if (timeOut == 0) {
		return mscReturnTimeOut;
	}

	return (int) length;
}

int flash_read(uint32_t address, void * data, uint32_t length) {
	// read from pointer to address
	uint32_t * pdata = (uint32_t *) address;

	// copy data from address pointer to buffer
	memcpy(data, pdata, length);

	return length;
}


// Erase <number> pages from start_address
int flash_erase(uint32_t start_address, uint32_t length) {
	PRINTF("FLASH ERASE IN \n");
	unsigned int i = 0;
	uint32_t number = (length / FLASH_PAGE_SIZE);

	if (length % FLASH_PAGE_SIZE != 0)
		number++;

	INT_Disable();

	for (i = 0; i < number; i++) {
		MSC_ErasePage((uint32_t *) start_address + i * FLASH_PAGE_SIZE);
	}
	// Enable interrupts
	INT_Enable();

	PRINTF("FLASH ERASE OUT \n");
	return length;
}

int flash_compread(uint32_t address, void * data, uint32_t length) {
	PRINTF("FLASH COMPREAD IN \n");
	uint32_t i = 0;

	for (i = 0; i < length; i++) {
		((uint8_t *) data)[i] = ~(*(uint8_t *) (address + i));
	}

	PRINTF("FLASH COMPREAD OUT \n");

	return length;
}

int flash_compwrite(uint32_t address, const char * data, uint32_t length) {
	PRINTF("FLASH COMPWRITE IN to address: 0x%08x with length: %d \n", address, length);
	msc_Return_TypeDef retval = mscReturnOk;
	uint32_t i = 0;
	uint32_t tmp_buf;

	ENERGEST_ON(ENERGEST_TYPE_FLASH_WRITE);
	// Disable interrupts.
	INT_Disable();

	for (i = 0; i < length; i = i + 4) {
		memcpy(&tmp_buf, data + i, 4);
		tmp_buf = ~tmp_buf;
		retval = MSC_WriteWord((uint32_t *) (address + i), (const void*) &tmp_buf, 4);
	}

	INT_Enable();
	ENERGEST_OFF(ENERGEST_TYPE_FLASH_WRITE);

	PRINTF("FLASH COMPWRITE OUT \n");
	if (retval != mscReturnOk) {
		PRINTF("ERROR: RETURNED %d \n", retval);
		return retval;
	} else {
		PRINTF("WROTE %d BYTES TO MEMORY \n", length);
		return length;
	}
}
