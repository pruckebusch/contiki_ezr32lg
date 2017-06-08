#include <stdlib.h>
#include <malloc.h>
#include <string.h>
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
static uint32_t datamemory_aligned[ELFLOADER_DATAMEMORY_SIZE];
static uint8_t *datamemory = (uint8_t *) datamemory_aligned;

#if TEXT_IN_ROM
	//static const uint32_t textmemory[ELFLOADER_TEXTMEMORY_SIZE] __attribute__ ((aligned (2048))) = {0};
	static const uint32_t textmemory[ELFLOADER_TEXTMEMORY_SIZE] = {0};
	uint32_t text_addr = 0x0001F800;
#else
	static uint32_t textmemory[ELFLOADER_TEXTMEMORY_SIZE];
#endif

#define READSIZE 				sizeof(datamemory_aligned)

// Supported relocations
#define R_ARM_ABS32                2
#define R_ARM_THM_CALL            10
#define R_ARM_THM_JUMP24          30

#define ELF32_R_TYPE(info)      ((unsigned char)(info))


void relJmpCall(int input_fd, elf32_addr relAddr, elf32_addr symAddr, uint32_t addend) {
  uint32_t relValue = 0;
  uint16_t upper_insn = ((uint16_t *) &addend)[0];
  uint16_t lower_insn = ((uint16_t *) &addend)[1];
  //uint16_t upper_insn = 0xF7FF;
  //uint16_t lower_insn = 0xFFFE;
  uint32_t S = (upper_insn >> 10) & 1;
  uint32_t J1 = (lower_insn >> 13) & 1;
  uint32_t J2 = (lower_insn >> 11) & 1;
  printf("relAddr 0x%08x, upper 0x%04x, lower 0x%04x, S 0x%08x, J1 0x%08x, J2 0x%08x\n", relAddr, upper_insn, lower_insn, S, J1, J2);

  int32_t offset = (S << 24) | /* S     -> offset[24] */
    ((~(J1 ^ S) & 1) << 23) | /* J1    -> offset[23] */
    ((~(J2 ^ S) & 1) << 22) | /* J2    -> offset[22] */
    ((upper_insn & 0x03ff) << 12) | /* imm10 -> offset[12:21] */
    ((lower_insn & 0x07ff) << 1); /* imm11 -> offset[1:11] */
  //~ printf("offset 0x%08x, %d\n", offset, offset);
  if (offset & 0x01000000)
    offset -= 0x02000000;
  //~ printf("offset 0x%08x, %d\n", offset, offset);
  offset += symAddr - relAddr;
  //~ printf("offset 0x%08x, %d\n", offset, offset);
  S = (offset >> 24) & 1;
  J1 = S ^ (~(offset >> 23) & 1);
  J2 = S ^ (~(offset >> 22) & 1);
  
  upper_insn = ((upper_insn & 0xf800) | (S << 10) | ((offset >> 12) & 0x03ff));
  ((uint16_t*) &relValue)[1] = upper_insn;

  lower_insn = ((lower_insn & 0xd000) | (J1 << 13) | (J2 << 11)
                | ((offset >> 1) & 0x07ff));
  ((uint16_t*) &relValue)[0] = lower_insn;
  printf("retValue 0x%08x, relAddr 0x%08x, upper 0x%04x, lower 0x%04x, S 0x%08x, J1 0x%08x, J2 0x%08x\n", relValue, relAddr, upper_insn, lower_insn, S, J1, J2);
  if(cfs_write(input_fd, &relValue, 4) != 4){
	  printf("CFS ERROR!!!!!\n");
  }
  //flash_compwrite(relAddr, (const char *) &relValue, 4, 0);
}

int elfloader_arch_relocate(int input_fd, unsigned int sectionoffset,
		char *sectionaddr, struct elf32_rela *rela, char *addr) {

    PRINTF("ARCH RELOCATE: FD: %d, SECTIONOFFSET: %p, SECTIONBASE: %p, ADDR: %p \n", input_fd, sectionoffset, sectionaddr, addr);

	uint32_t type = ELF32_R_TYPE(rela->r_info);

	PRINTF("elfloader: arch_relocate \n");
	PRINTF("elfloader: offset: 0x%08X, type: %d\n", rela->r_offset, type);

	int s = -1;
	// set current fd to relocation address
	s = cfs_seek(input_fd, sectionoffset + rela->r_offset, CFS_SEEK_SET);
	if (s == -1) {
		PRINTF("Invalid file descriptor or offset (%d) exceeds max/min file boundary\n", s);
		// ToDo add missing return types
		return 9;
	}

	switch (type) {
	case R_ARM_ABS32: {
		// relocation calculation: (S + A) | T
		// with T = 0
		PRINTF("addend: %lx, addr: %p\n", rela->r_addend, addr);
		addr += rela->r_addend;
		cfs_write(input_fd, &addr, sizeof(char*));
		//~ if((uint32_t) sectionaddr < 0x2000000){
			//~ flash_compwrite((uint32_t) (sectionaddr + rela->r_offset), (const char *) &addr, 4, 0);	
		//~ } else {
			//~ memcpy(sectionaddr + rela->r_offset,&addr,4);
		//~ }
		PRINTF("sectionadd + rela->r_offset: %p, addr: %p\n", sectionaddr + rela->r_offset, addr);
		
		/*int32_t addend;
		cfs_read(input_fd, (char *) &addend, 4);
		addr += addend;
	    cfs_seek(input_fd, -4, CFS_SEEK_CUR);
		cfs_write(input_fd, &addr, 4);
		
		PRINTF("elfloader: addend %d \n", addend);
		PRINTF("Addr in FLASH to write to: %p, addr in RAM: %p\n", sectionaddr + rel->r_offset, addr);
		*/
	}
		break;
	case R_ARM_THM_CALL:
	case R_ARM_THM_JUMP24:
	{
		
		//~ uint16_t instr[2];
		//~ cfs_read(input_fd, (char *)instr, 4);
		//~ uint16_t upper = instr[0];
        //~ uint16_t lower = instr[1];
        uint32_t tgt_fulloffset = (uint32_t) addr;
        uint32_t locoffset = ((uint32_t) sectionaddr) + rela->r_offset;
        printf("relocating %p(0x%08x) to %p(0x%08x) addend (0x%08x)\n", locoffset, locoffset, tgt_fulloffset, tgt_fulloffset, rela->r_addend);
        relJmpCall(input_fd, locoffset, tgt_fulloffset, rela->r_addend);
		break;
	}
	/*{
		uint16_t instr[2];
		cfs_read(input_fd, (char *)instr, 4);
		uint32_t i, j;
		int32_t addend, tmpAddr;
		int32_t final_offset, offset;
		i = instr[1];
		j = instr[0];
		j = j << 16;
		i = i | j;
		PRINTF("R_ARM_THM_CALL instruction: %lx\n", i);

		i = (i << 2) & 0x00FFFFFF;
		if ((i & 0x00800000)!=0)
			i = i | 0xFF000000;
		addend = (int32_t)i;

		PRINTF("\tAddend : %lx (%ld)\n", addend, addend);
		PRINTF("\tJump target (calculated by Contiki) : %p\n", addr);
		PRINTF("\tJump target (real) : %p\n", &puts);
		PRINTF("\tSection address : %p\n", sectionaddr);
		PRINTF("\tProgram Counter (PC) : %p\n", sectionaddr + rela->r_offset);
		PRINTF("\tProgram Counter + 8 (PC) : %p\n", sectionaddr + rela->r_offset + 8);

		tmpAddr = (uint32_t)addr;
		if ((tmpAddr & 0x1) != 0)
			tmpAddr = tmpAddr & (~1); // remove last bit if set

		offset = tmpAddr - ((uint32_t)sectionaddr + rela->r_offset);
		offset -= 4; // the adjusment for Thumb instructions

		PRINTF("\tCalculated offset (%ld): %lx\n", offset, offset);

		// keep 11 bits
		j = offset & 0x007FFFFF;
		j >>= 12;
		PRINTF("\tThe first half is %lx\n", j);
		i = offset & 0x00000FFF;
		i >>= 1;
		PRINTF("\tThe second half is %lx\n", i);
		instr[1] = (instr[1] & 0xF800) | (uint16_t)(i);


		instr[0] = (instr[0] & 0xF800) | (uint16_t)j;

		PRINTF("\tinstr[0]: %x, instr[1]: %x\n", instr[0], instr[1]);

		cfs_seek(input_fd, -4, CFS_SEEK_CUR);
		cfs_write(input_fd, &instr, 4);
		}
		*/
		
		
		
		/*uint16_t instr[2];
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
		*/
	
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
	//~ if (size > sizeof(textmemory)) {
		//~ PRINTF("RESERVED FLASH TOO SMALL\n");
	//~ }
	//~ PRINTF("TEXTMEMORY LOCATION: %p 0x%08x \n", (void*)text_addr, text_addr);
	//~ flash_erase((uint32_t) &textmemory, 2048);
	//~ return (void *) textmemory;
	PRINTF("TEXTMEMORY LOCATION: %p 0x%08x \n", (void*)text_addr, text_addr);
	flash_erase(text_addr, 2048);
	return (void*) text_addr;
}

void elfloader_arch_write_rom(int fd, unsigned short textoff, unsigned int size, char *mem) {
#if TEXT_IN_ROM
	PRINTF("FD: %d, TEXTOFF: %p, SIZE: %d, MEM: %p \n", fd, textoff, size, mem);

	uint32_t tmp_buf[128] = {0};
	int nbytes;
	// set fd pointer to memory offset
	cfs_seek(fd, textoff, CFS_SEEK_SET);

	// read data from file into RAM
	nbytes = cfs_read(fd, (unsigned char *) datamemory, size);
	PRINTF("Before ROM write\n");
	int i;
	for (i = 0; i < size; i++) {
		PRINTF("0x%02X,", datamemory[i]);
		if (((i + 1) % 20) == 0) {
			PRINTF("\n");
		}
	}
	PRINTF("\n");

	// write data to flash
	flash_compwrite( (uint32_t) mem , datamemory, size, 0);
	flash_compread((uint32_t) mem , datamemory, size, 0);
	
	PRINTF("After ROM write\n");
	for (i = 0; i < size; i++) {
		PRINTF("0x%02X,", ((uint8_t*)datamemory)[i]);
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
