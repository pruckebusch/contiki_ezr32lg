#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

#define FLASH_PAGE_SIZE 		2048

void flash_init(void);
int flash_erase(uint32_t start_address, uint32_t length);
int flash_comread(uint32_t address, void * data, uint32_t length, uint8_t invert_bits);
int flash_compwrite(uint32_t address, const char * data, uint32_t length, uint8_t invert_bits);

#endif /* __FLASH_H__ */

/** @} */
/** @} */

