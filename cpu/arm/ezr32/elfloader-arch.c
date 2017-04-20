#include <stdlib.h>
#include <malloc.h>

#include "elfloader.h"
#include "flash.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) do {} while (0)
#endif

struct elf32_rel {
	elf32_addr r_offset;       // Location to be relocated
	elf32_word r_info;         // Relocation type and symbol index
};

#define TEXT_IN_ROM				1

// ToDo
// word-aligned
static uint16_t datamemory_aligned[ELFLOADER_DATAMEMORY_SIZE];
static uint8_t *datamemory = (uint8_t *) datamemory_aligned;

#if TEXT_IN_ROM
	static const uint16_t textmemory[ELFLOADER_TEXTMEMORY_SIZE] = {0};
#else
	static uint16_t textmemory[ELFLOADER_TEXTMEMORY_SIZE];
#endif

#define READSIZE 				sizeof(datamemory_aligned)

// Supported relocations
#define R_ARM_ABS32				2
#define R_ARM_THM_CALL			10

#define ELF32_R_TYPE(info)      ((unsigned char)(info))

int elfloader_arch_relocate(int input_fd, unsigned int sectionoffset,
		char *sectionaddr, struct elf32_rel *rel, char *addr) {

    PRINTF("ARCH RELOCATE: FD: %d, SECTIONOFFSET: %p, SECTIONBASE: %p, ADDR: %p \n", input_fd, sectionoffset, sectionaddr, addr);

	uint32_t type = ELF32_R_TYPE(rel->r_info);

	PRINTF("elfloader: arch_relocate \n");
	PRINTF("elfloader: offset: 0x%08X, type: %d\n", rel->r_offset, type);

	int s = -1;
	// set current fd to relocation address
	s = cfs_seek(input_fd, sectionoffset + rel->r_offset, CFS_SEEK_CUR);
	if (s == -1) {
		PRINTF("Invalid file descriptor or offset (%d) exceeds max/min file boundary\n", s);
		// ToDo add missing return types
		return 9;
	}

	switch (type) {
	case R_ARM_ABS32: {
		// relocation calculation: (S + A) | T
		// with T = 0
		int32_t addend;
		cfs_read(input_fd, (char *) &addend, 4);
		addr += addend;
	    cfs_seek(input_fd, -4, CFS_SEEK_CUR);
		cfs_write(input_fd, &addr, 4);

		PRINTF("elfloader: addend %d \n", addend);
		PRINTF("Addr in FLASH to write to: %p, addr in RAM: %p\n", sectionaddr + rel->r_offset, addr);
	}
		break;
	case R_ARM_THM_CALL: {
		uint16_t instr[2];
		int32_t offset;
		char *base;
		cfs_read(input_fd, (char *) instr, 4);
		cfs_seek(input_fd, -4, CFS_SEEK_CUR);

		// ignore addend, always zero for calls to symbols
		base = sectionaddr + (rel->r_offset + 4);
		if (((instr[1]) & 0xe800) == 0xe800) {
			// BL or BLX
			if (((uint32_t) addr) & 0x1) {
				// BL
				instr[1] |= 0x1800;
			} else {
				// BLX
				instr[1] &= ~0x1800;
				instr[1] |= 0x0800;
			}
		}

		// adjust address for BLX
		if ((instr[1] & 0x1800) == 0x0800) {
			addr = (char *) ((((uint32_t) addr) & 0xfffffffd)
					| (((uint32_t) base) & 0x00000002));
		}
		offset = addr - (sectionaddr + (rel->r_offset + 4));
		PRINTF("elfloader-arm.c: offset %d\n", (int )offset);
		if (offset < -(1 << 22) || offset >= (1 << 22)) {
			PRINTF("elfloader-arm.c: offset %d too large for relative call\n",
					(int )offset);
		}
		PRINTF("%p: %04x %04x  offset: %d addr: %p\n", sectionaddr +rel->r_offset, instr[0], instr[1], (int)offset, addr);
		instr[0] = (instr[0] & 0xf800) | ((offset >> 12) & 0x07ff);
		instr[1] = (instr[1] & 0xf800) | ((offset >> 1) & 0x07ff);

		// cfs_seek(input_fd, sectionoffset + rel->r_offset, CFS_SEEK_SET);
		cfs_write(input_fd, &instr, 4);

		PRINTF("cfs_write: %04x %04x\n", instr[0], instr[1]);
	}
		break;
	default:
		PRINTF("elfloader-arm.c: unsupported relocation type %d\n", type);
		// ToDo add missing return types
		return 8;
	}

	return ELFLOADER_OK;
}

void *elfloader_arch_allocate_ram(int size) {
	// return the datamemory array
	if (size > sizeof(datamemory_aligned)) {
		PRINTF("RESERVED RAM TOO SMALL\n");
	}
	PRINTF("DATAMEMORY LOCATION: 0x%08x \n", &datamemory);
	return datamemory;
}

void *elfloader_arch_allocate_rom(int size) {
	if (size > sizeof(textmemory)) {
		PRINTF("RESERVED FLASH TOO SMALL\n");
	}
	PRINTF("TEXTMEMORY LOCATION: 0x%08x \n", &textmemory);
	return (void *) textmemory;
}

void elfloader_arch_write_rom(int fd, unsigned short textoff, unsigned int size,
		char *mem) {
#if TEXT_IN_ROM
	PRINTF("FD: %d, TEXTOFF: %p, SIZE: %d, MEM: %p \n", fd, textoff, size, mem);

	uint32_t tmp_buf[128] = {0};
	int nbytes;
	// set fd pointer to memory offset
	cfs_seek(fd, textoff, CFS_SEEK_SET);

	// read data from file into RAM
	nbytes = cfs_read(fd, (unsigned char *) datamemory, size);

	int i;
	for (i = 0; i < size; i++) {
		PRINTF("0x%02X,", datamemory[i]);
		if (((i + 1) % 20) == 0) {
			PRINTF("\n");
		}
	}
	PRINTF("\n");

	uint32_t *addr = mem;

	// write data to flash
	flash_write(addr, datamemory, size);

	flash_read(addr, tmp_buf, size);

	for(i = 0; i < size; i++) {
		PRINTF("0x%02X,", tmp_buf[i]);
		if (((i + 1) % 20) == 0) {
			PRINTF("\n");
		}
	}
	PRINTF("\n");

#else
	cfs_seek(fd, textoff, CFS_SEEK_SET);
	cfs_read(fd, (unsigned char *) mem, size);
#endif

/*
	uint32_t ptr;
	int nbytes;
	cfs_seek(fd, textoff, CFS_SEEK_SET);
	cfs_seek(fd, textoff, CFS_SEEK_SET);

	for (ptr = 0; ptr < size; ptr += READSIZE) {
		// Read data from file into RAM
		nbytes = cfs_read(fd, (unsigned char *) datamemory, READSIZE);

		int i;
		for(i = 0; i < nbytes; i++) {
			// PRINTF("0x%02X,", datamemory[i]);
			if( ((i+1) % 20) == 0 ) {
				// PRINTF("\n");
			}
		}

		// Write data to flash
		flash_compwrite((uint32_t) mem, datamemory, nbytes);

		PRINTF("Where to write? %p \n", &mem);
	}
*/
	/*


*/
	  /*
	// when using a const array,
	// use flash_compwrite to overwrite read-only array
	int i; int nbytes;
	unsigned int ptr;
	unsigned short *flashptr;
	flashptr = (unsigned short *)mem;

	cfs_seek(fd, textoff, CFS_SEEK_SET);
	for (ptr = 0; ptr < size; ptr += READSIZE) {

		// Read data from file into RAM.
		nbytes = cfs_read(fd, (unsigned char *) datamemory, READSIZE);

		// Clear flash page on 2048 byte boundary.
		if ((((unsigned short) flashptr) & 0x07ff) == 0) {
			flash_erase(flashptr, 0x07ff);
		}
	}

	PRINTF("FLASHPTR: 0x%08X, &FLASHPTR: 0x%08X \n", flashptr, &flashptr);

	for (i = 0; i < READSIZE / 2; ++i) {
		flash_compwrite(flashptr, ((unsigned short*) datamemory)[i], nbytes);
		++flashptr;
	}
	*/

/*
	int nbytes;
	cfs_seek(fd, textoff, CFS_SEEK_SET);
	cfs_seek(fd, textoff, CFS_SEEK_SET);

	PRINTF("NEED TO STORE %d bytes \n", size);
	PRINTF("READ FROM 0x%08X \n", mem);

	uint8_t *buf;
	buf = mem - size;

	int i;
	for(i = 0; i < size; i++) {
		PRINTF("0x%02X,", buf[i]);
	}

	for (ptr = 0; ptr < size; ptr += READSIZE) {
		// read data from file into RAM
		nbytes = cfs_read(fd, (unsigned char *) datamemory, READSIZE);


		PRINTF("Storing %d bytes \n", nbytes);
		PRINTF("Data: \n\n");

		int i; int j = 1;
		for(i = 0; i < nbytes; i++) {
			PRINTF("0x%02X,", datamemory[i]);
			if (j % 20 == 0 && j != 0) {
				printf("\n");
			}
			j++;
		}

		// write data to flash, don't use file / file descriptor
		// stored at address where the const array resides
		// by using these addresses, we can change the values of the array contents
		flash_compwrite((uint32_t) mem, datamemory, nbytes);
	}*/
}
