#include <lowlevelio.h>


static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ __volatile__ ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void io_wait(void) {
    __asm__ __volatile__ ("outb %%al, $0x80" : : "a"(0));
}

void ata_wait_bsy() {
    while (inb(ATA_PRIMARY_IO_BASE + 0x07) & 0x80);
}

void ata_wait_drq() {
    while (!(inb(ATA_PRIMARY_IO_BASE + 0x07) & 0x08));
}

void ata_init(void) {

}

void ata_read_sector(uint32_t lba, uint8_t *buffer) {
    ata_wait_bsy();
    outb(ATA_PRIMARY_CONTROL_BASE, 0x00); 

    outb(ATA_PRIMARY_IO_BASE + 0x02, 0x01); 
    outb(ATA_PRIMARY_IO_BASE + 0x03, (uint8_t)(lba));
    outb(ATA_PRIMARY_IO_BASE + 0x04, (uint8_t)(lba >> 8));
    outb(ATA_PRIMARY_IO_BASE + 0x05, (uint8_t)(lba >> 16));
    outb(ATA_PRIMARY_IO_BASE + 0x06, 0xE0 | ((lba >> 24) & 0x0F)); 

    outb(ATA_PRIMARY_IO_BASE + 0x07, 0x20); 

    ata_wait_bsy();
    ata_wait_drq();

    for (int i = 0; i < ATA_SECTOR_SIZE / 2; i++) {
        ((uint16_t *)buffer)[i] = inw(ATA_PRIMARY_IO_BASE);
    }
}
