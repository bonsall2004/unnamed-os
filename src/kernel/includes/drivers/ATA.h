/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include <cstdint>

// ATA I/O ports
#define ATA_PRIMARY_IO 0x1F0
#define ATA_PRIMARY_CTRL 0x3F6
#define ATA_SECONDARY_IO 0x170
#define ATA_SECONDARY_CTRL 0x376

// ATA commands
#define ATA_CMD_IDENTIFY 0xEC
#define ATA_CMD_READ_PIO 0x20
#define ATA_CMD_WRITE_PIO 0x30

// Status flags
#define ATA_SR_BSY 0x80
#define ATA_SR_DRQ 0x08

// Device types
#define ATA_DEV_MASTER 0x00
#define ATA_DEV_SLAVE 0x10

struct ata_device
{
  uint16_t base;
  uint16_t ctrl;
  uint8_t slave;
  uint8_t type; // 0: ATA, 1: ATAPI
  uint16_t signature;
  uint16_t capabilities;
  uint32_t command_sets;
  uint32_t size;
  char model[41];
};

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t val);
uint16_t intw(uint16_t port);
void io_wait(void);
void ata_wait_busy(uint16_t base);
void ata_wait_drq(uint16_t base);
void ata_select_device(uint16_t base, uint8_t slave);
int ata_identify(uint16_t base, uint8_t slave, struct ata_device* dev);
void ata_initialize(struct ata_device* dev);
