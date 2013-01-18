#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "types.h"

#define MB_FLAG_MEMORY 1
#define MB_FLAG_DEVICE 2
#define MB_FLAG_CMDLINE 4
#define MB_FLAG_MODULES 8
#define MB_FLAG_SYM_AOUT 16
#define MB_FLAG_SYM_ELF 32
#define MB_FLAG_MMAP 64
#define MB_FLAG_DRIVES 128
#define MB_FLAG_CFGTABLE 256
#define MB_FLAG_BOOTLOADER_NAME 512
#define MB_FLAG_APM 1024

#define MB_MEMORY_AVAILABLE 1
#define MB_MEMORY_RESERVED 2

struct mb_aout_t {
	uint32_t tabsize;
	uint32_t strsize;
	uint32_t addr;
	uint32_t reserved;
};

struct mb_elf_t {
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
};

struct mb_module_t {
	uint32_t mod_start;
	uint32_t mod_end;
	char *cmdline;
	uint32_t reserved;
}__attribute__((packed));

struct mb_mmap_t {
	uint32_t size;
	uint64_t base;
	uint64_t length;
	uint32_t type;
}__attribute__((packed));

struct mb_info_t {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t bootdevice;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	union {
		struct mb_aout_t aout_sym;
		struct mb_elf_t elf_sec;
	} u;
	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
}__attribute__ ((packed));

#endif
