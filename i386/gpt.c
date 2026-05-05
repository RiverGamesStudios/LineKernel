#include "config.h"

#ifdef gpt
#ifdef ide
#include "gpt.h"
#include "ide.h"
#include "third-party/printf.h"
#define kprintf printf

typedef struct {
	uint8_t signature[8];		// Should be "EFI PART"
	uint32_t revision;
	uint32_t header_size;
	uint32_t header_crc32;		// CRC32 of the header (with this field set to 0)
	uint32_t reserved0;
	uint64_t current_lba;		// Usually 1
	uint64_t backup_lba;		// Last LBA of the disk
	uint64_t first_usable_lba;
	uint64_t last_usable_lba;
	uint8_t disk_guid[16];
	uint64_t partition_entry_lba;	// Usually 2
	uint32_t num_partition_entries;
	uint32_t partition_entry_size;	// Usually 128 bytes
	uint32_t partition_array_crc32;
} __attribute__((packed)) gpt_header_t;

typedef struct {
	uint8_t partition_type_guid[16];
	uint8_t unique_partition_guid[16];
	uint64_t starting_lba;
	uint64_t ending_lba;
	uint64_t attributes;
	uint16_t partition_name[36];	// UTF-16LE
} __attribute__((packed)) gpt_entry_t;

#endif
#endif
