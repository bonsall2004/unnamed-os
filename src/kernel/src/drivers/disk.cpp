/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <disk.h>
#include <ATA.h>
#include <cstdint>


// im sorry about this code 
// is you can find a better way of doing jt be my gest

extern "C"{
int ata_read_sector(struct ata_device* dev, uint64_t lba, uint8_t* buffer) {
  uint16_t base = dev->base;
  uint8_t slave = dev->slave;

  ata_select_device(base, slave);
  ata_wait_busy(base);

  outb(base + 2, 1);
  outb(base + 3, (uint8_t) lba);
  outb(base + 4, (uint8_t)(lba >> 8));
  outb(base + 5, (uint8_t)(lba >> 16));
  outb(base + 6, 0xE0 | (slave << 4) | ((lba >> 24) & 0x0F));
  outb(base + 7, ATA_CMD_READ_SECTORS);

  ata_wait_busy(base);
  ata_wait_drq(base);

  for (int i = 0; i < SECTOR_SIZE / 2; i++) {
    ((uint16_t*)buffer)[i] = inw(base);
  }

  return 1;
}
uint64_t find_partition_with_guid(struct ata_device* device, const uint8_t* target_guid) {
  uint8_t buffer[SECTOR_SIZE];

  if (!ata_read_sector(device, GPT_HEADER_LBA, buffer)) {
    printf("Error reading GPT header\n");
    return 0;
  }

  GPTHeader* gpt_header = (GPTHeader*) buffer;

  if (gpt_header->signature != GPT_SIGNATURE) {
    printf("Invalid GPT signature\n");
    return 0;
  }

  uint32_t num_entries = gpt_header->num_partition_entries;
  uint32_t entry_size = gpt_header->partition_entry_size;
  uint64_t entry_lba = gpt_header->partition_entry_lba;
  uint32_t num_sectors = (num_entries * entry_size + SECTOR_SIZE - 1) / SECTOR_SIZE;

  GPTPartitionEntry* entries = (GPTPartitionEntry*) malloc(num_sectors * SECTOR_SIZE);
  if (!entries) {
    printf("Memory allocation error\n");
    return 0;
  }

  for (uint32_t i = 0; i < num_sectors; i++) {
    if (!ata_read_sector(device, entry_lba + i, ((uint8_t*)entries) + i * SECTOR_SIZE)) {
      printf("Error reading partition entries\n");
      free(entries);
      return 0;
    }
  }

  uint64_t offset = 0;
  for (uint32_t i = 0; i < num_entries; i++) {
    GPTPartitionEntry* entry = (GPTPartitionEntry*)((uint8_t*)entries + i * entry_size);
    if (memcmp(entry->partition_type_guid, target_guid, 16) == 0) {
      offset = entry->first_lba;
      break;
    }
  }

  free(entries);
  return offset;
}
uint64_t find_partition_start_lba(struct ata_device* device, const uint8_t* partition_guid) {
  uint8_t buffer[SECTOR_SIZE];

  if (!ata_read_sector(device, GPT_HEADER_LBA, buffer)) {
    printf("Error reading GPT header\n");
    return 0;
  }

  GPTHeader* gpt_header = (GPTHeader*)buffer;

  if (gpt_header->signature != GPT_SIGNATURE) {
    printf("Invalid GPT signature\n");
    return 0;
  }

  uint32_t num_entries = gpt_header->num_partition_entries;
  uint32_t entry_size = gpt_header->partition_entry_size;
  uint64_t entry_lba = gpt_header->partition_entry_lba;
  uint32_t num_sectors = (num_entries * entry_size + SECTOR_SIZE - 1) / SECTOR_SIZE;

  GPTPartitionEntry* entries = (GPTPartitionEntry*)malloc(num_sectors * SECTOR_SIZE);
  if (!entries) {
    printf("Memory allocation error\n");
    return 0;
  }

  for (uint32_t i = 0; i < num_sectors; i++) {
    if (!ata_read_sector(device, entry_lba + i, ((uint8_t*)entries) + i * SECTOR_SIZE)) {
      printf("Error reading partition entries\n");
      free(entries);
      return 0;
    }
  }

  uint64_t start_lba = 0;
  for (uint32_t i = 0; i < num_entries; i++) {
    GPTPartitionEntry* entry = (GPTPartitionEntry*)((uint8_t*)entries + i * entry_size);
    if (memcmp(entry->unique_partition_guid, partition_guid, 16) == 0) {
      start_lba = entry->first_lba;
      break;
    }
  }

  free(entries);
  return start_lba;
}

uint64_t find_partition_last_lba(struct ata_device* device, const uint8_t* partition_guid) {
  uint8_t buffer[SECTOR_SIZE];

  if (!ata_read_sector(device, GPT_HEADER_LBA, buffer)) {
    printf("Error reading GPT header\n");
    return 0;
  }

  GPTHeader* gpt_header = (GPTHeader*)buffer;

  if (gpt_header->signature != GPT_SIGNATURE) {
    printf("Invalid GPT signature\n");
    return 0;
  }

  uint32_t num_entries = gpt_header->num_partition_entries;
  uint32_t entry_size = gpt_header->partition_entry_size;
  uint64_t entry_lba = gpt_header->partition_entry_lba;
  uint32_t num_sectors = (num_entries * entry_size + SECTOR_SIZE - 1) / SECTOR_SIZE;

  GPTPartitionEntry* entries = (GPTPartitionEntry*)malloc(num_sectors * SECTOR_SIZE);
  if (!entries) {
    printf("Memory allocation error\n");
    return 0;
  }

  for (uint32_t i = 0; i < num_sectors; i++) {
    if (!ata_read_sector(device, entry_lba + i, ((uint8_t*)entries) + i * SECTOR_SIZE)) {
      printf("Error reading partition entries\n");
      free(entries);
      return 0;
    }
  }

  uint64_t last_lba = 0;
  for (uint32_t i = 0; i < num_entries; i++) {
    GPTPartitionEntry* entry = (GPTPartitionEntry*)((uint8_t*)entries + i * entry_size);
    if (memcmp(entry->unique_partition_guid, partition_guid, 16) == 0) {
      last_lba = entry->last_lba;
      break;
    }
  }

  free(entries);
  return last_lba;
}


int read_between_lbams(struct ata_device* device, uint64_t start_lba, uint64_t end_lba, uint8_t* buffer) {
  uint64_t current_lba = start_lba;
  uint64_t remaining_sectors = end_lba - start_lba + 1;
  int buffer_offset = 0;

  while (remaining_sectors > 0) {
    uint16_t sectors_to_read = (remaining_sectors > 65535) ? 65535 : (uint16_t)remaining_sectors;
    if (!ata_read_sectors(device, current_lba, sectors_to_read, buffer + buffer_offset * SECTOR_SIZE)) {
      printf("Error reading sectors\n");
      return 0;
    }
    current_lba += sectors_to_read;
    buffer_offset += sectors_to_read;
    remaining_sectors -= sectors_to_read;
  }

  return 1;
}


}
