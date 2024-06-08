#include <stdint.h>

#define ATA_PRIMARY_IO_BASE 0x1F0
#define ATA_PRIMARY_CONTROL_BASE 0x3F6
#define ATA_SECTOR_SIZE 512

// Function prototypes
void ata_init(void);
void ata_read_sector(uint32_t lba, uint8_t *buffer);
