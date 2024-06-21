/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include <cstdint>
#include <ATA.h>

#define SECTOR_SIZE 512
#define GPT_HEADER_LBA 1
#define GPT_SIGNATURE 0x5452415020494645ULL

export "C"{

typedef struct {
  uint64_t signature;
  uint32_t revision;
  uint32_t header_size;
  uint32_t header_crc32;
  uint32_t reserved;
  uint64_t current_lba;
  uint64_t backup_lba;
  uint64_t first_usable_lba;
  uint64_t last_usable_lba;
  uint8_t disk_guid[16];
  uint64_t partition_entry_lba;
  uint32_t num_partition_entries;
  uint32_t partition_entry_size;
  uint32_t partition_array_crc32;
} GPTHeader;
 
typedef struct {
  uint8_t partition_type_guid[16];
  uint8_t unique_partition_guid[16];
  uint64_t first_lba;
  uint64_t last_lba;
  uint64_t attributes;
  uint16_t partition_name[36];
} GPTPartitionEntry;
  int ata_read_sector(struct ata_device* dev, uint64_t lba, uint8_t* buffer);
  uint64_t find_partition_with_guid(struct ata_device* device, const uint8_t* target_guid);
  uint64_t find_partition_start_lba(struct ata_device* device, const uint8_t* partition_guid);
  uint64_t find_partition_last_lba(struct ata_device* device, const uint8_t* partition_guid);
  int read_between_lbams(struct ata_device* device, uint64_t start_lba, uint64_t end_lba, uint8_t* buffer);
}
