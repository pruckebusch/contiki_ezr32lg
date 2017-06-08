#ifndef CFS_COFFEE_ARCH_H
#define CFS_COFFEE_ARCH_H

#include "dev/flash.h"
#include "contiki-conf.h"

// FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 262144
// 0x0FE00000 + 2048 bytes = 0xFE00500 (2048 bytes = 0x0000500)
//
// defines from ezr32lg330f256r55.h
// #define FLASH_BASE           (0x00000000UL) /**< Flash Base Address */
// #define FLASH_SIZE           (0x00040000UL) /**< Available Flash Memory */
// 128 * 2048 = 256 bytes (total flash memory)
// #define FLASH_PAGE_SIZE      2048           /**< Flash Memory page size */

#define FLASH_START					0x00020000
// FLASH_END = 0x0FE04000
// FLASH_PAGE_SIZE					2048 // defined in flash.h
// reserved 128 kB of flash in config file
// only using 64 kB of flash
#define FLASH_PAGES					32

#define COFFEE_ADDRESS				0x00020000
#define COFFEE_PAGE_SIZE			(FLASH_PAGE_SIZE)
#define COFFEE_PAGES				((FLASH_PAGES*FLASH_PAGE_SIZE)/COFFEE_PAGE_SIZE)
#define COFFEE_SECTOR_SIZE			FLASH_PAGE_SIZE
#define COFFEE_START				(COFFEE_ADDRESS & ~(COFFEE_PAGE_SIZE-1))
#define COFFEE_SIZE					(COFFEE_PAGES*COFFEE_PAGE_SIZE)

#define COFFEE_NAME_LENGTH			16
#define COFFEE_MAX_OPEN_FILES		4
// The amount of file descriptor entries
#define COFFEE_FD_SET_SIZE			8
#define COFFEE_MICRO_LOGS			0
#define COFFEE_LOG_SIZE				128
#define COFFEE_LOG_TABLE_LIMIT		16
#define COFFEE_DYN_SIZE     		(COFFEE_PAGE_SIZE*1)

#define COFFEE_IO_SEMANTICS			1
#define COFFEE_APPEND_ONLY			0

// coffee types
typedef uint32_t coffee_page_t;

// mapping configuration parameters to storage device parameters
#define COFFEE_WRITE(buf, size, offset)				\
		flash_compwrite(COFFEE_START + (offset), (char *)(buf), (size), 1)

#define COFFEE_READ(buf, size, offset)				\
  		flash_compread(COFFEE_START + (offset), (char *)(buf), (size), 1)

#define COFFEE_ERASE(sector)					\
  		flash_erase(COFFEE_START + (sector) * COFFEE_SECTOR_SIZE, COFFEE_SECTOR_SIZE)

#define CFS_CONF_OFFSET_TYPE uint32_t

#endif
