#ifndef __FAT12_H__
#define __FAT12_H__

#include "kconfig.h"

#ifdef CONFIG_FAT12
#include <stdint.h>
#include "LineDrive.h"
#include "printf.h"

struct fat12_bpb {
	uint8_t jmp[3];
	char oem_id[8];
	uint16_t bytes_per_sector;
	uint8_t sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t num_fats;
	uint16_t root_dir_entries;
	uint16_t total_sectors_small;
	uint8_t media_descriptor;
	uint16_t sectors_per_fat;
	uint16_t sectors_per_track;
	uint16_t num_heads;
	uint32_t hidden_sectors;
	uint32_t total_sectors_large;
	uint8_t drive_number;
	uint8_t reserved;
	uint8_t boot_signature;
	uint32_t volume_id;
	char volume_label[11];
	char fs_type[8];
} __attribute__((packed));

int detect_fat12(drivesformat_t drive);
#endif

#endif
