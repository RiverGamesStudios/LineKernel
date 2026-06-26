/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "fat12.h"

#ifdef CONFIG_FAT12
int detect_fat12(drivesformat_t drive)
{
	uint8_t sector[512];

	/* Attempt to read sector 0 */
	if (read_drive_sector(drive, 0, (uint32_t*)sector) < 0) {
		printf("No drive detected or failed to read sector 0.\n");
		return -1;				/* No drive or read error */
	}

	/* Verify boot sector signature (0xAA55) */
	uint16_t boot_sig = sector[510] | (sector[511] << 8);

	if (boot_sig != 0xAA55) {
		printf("Drive present, but boot signature 0x%04X is invalid.\n", boot_sig);
		return 0;				/* Not a valid boot sector */
	}

	struct fat12_bpb* bpb = (struct fat12_bpb *)sector;

	/* Perform basic validations of FAT12 geometry */
	int is_fat12 = 1;

	if (bpb->bytes_per_sector != 512) {
		is_fat12 = 0;
	}
	if (bpb->media_descriptor != 0xF0 && bpb->media_descriptor != 0xF9) {
		/* 0xF0 = 1.44MB, 0xF9 = 720KB/1.2MB */
		is_fat12 = 0;
	}
	if (bpb->fs_type[0] != 'F' || bpb->fs_type[1] != 'A' || bpb->fs_type[2] != 'T' ||
		bpb->fs_type[3] != '1' || bpb->fs_type[4] != '2') {
		is_fat12 = 0;
	}

	if (is_fat12) {
		char oem[9];
		char label[12];

		for (int i = 0; i < 8; i++) {
			oem[i] = bpb->oem_id[i];
		}
		oem[8] = '\0';

		for (int i = 0; i < 11; i++) {
			label[i] = bpb->volume_label[i];
		}
		label[11] = '\0';

		printf("Valid FAT12 filesystem detected!\n");
		printf("  OEM ID:           %s\n", oem);
		printf("  Volume Label:     %s\n", label);
		printf("  Bytes/Sector:     %d\n", bpb->bytes_per_sector);
		printf("  Sectors/Cluster:  %d\n", bpb->sectors_per_cluster);
		printf("  Reserved Sectors: %d\n", bpb->reserved_sectors);
		printf("  Sectors/FAT:      %d\n", bpb->sectors_per_fat);
		printf("  Heads:            %d\n", bpb->num_heads);
		printf("  Sectors/Track:    %d\n", bpb->sectors_per_track);
		return 1;
	}

	printf("Disk present but does not contain a valid FAT12 filesystem.\n");
	return 0;
}
#endif
