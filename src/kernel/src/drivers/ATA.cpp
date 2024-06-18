/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <ATA.h>

void outb(uint16_t port, uint8_t val)
{
  __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
  uint8_t ret;
  __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void outw(uint16_t port, uint16_t val)
{
  __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}
uint16_t inw(uint16_t port)
{
  uint16_t ret;
  __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void io_wait(void)
{
  __asm__ volatile ("outb %%al, $0x80" : : "a"(0));
}

void ata_wait_busy(uint16_t base)
{
  while(inb(base + 7) & ATA_SR_BSY);
}

void ata_wait_drq(uint16_t base)
{
  while(!(inb(base + 7) & ATA_SR_DRQ));
}

void ata_select_device(uint16_t base, uint8_t slave)
{
  outb(base + 6, 0xA0 | (slave << 4));
  io_wait();
}

int ata_identify(uint16_t base, uint8_t slave, struct ata_device* dev)
{
  ata_select_device(base, slave);
  ata_wait_busy(base);

  outb(base + 7, ATA_CMD_IDENTIFY);
  io_wait();

  if(inb(base + 7) == 0) return 0;  // No device

  ata_wait_busy(base);
  ata_wait_drq(base);

  for(int i = 0; i < 256; i++)
  {
    ((uint16_t*)dev)[i] = inw(base);
  }

  return 1;
}

void ata_initialize(struct ata_device* dev)
{
  if(ata_identify(ATA_PRIMARY_IO, ATA_DEV_MASTER, dev))
  {
    dev->base = ATA_PRIMARY_IO;
    dev->ctrl = ATA_PRIMARY_CTRL;
    dev->slave = ATA_DEV_MASTER;
  }
  else if(ata_identify(ATA_PRIMARY_IO, ATA_DEV_SLAVE, dev))
  {
    dev->base = ATA_PRIMARY_IO;
    dev->ctrl = ATA_PRIMARY_CTRL;
    dev->slave = ATA_DEV_SLAVE;
  }
  else if(ata_identify(ATA_SECONDARY_IO, ATA_DEV_MASTER, dev))
  {
    dev->base = ATA_SECONDARY_IO;
    dev->ctrl = ATA_SECONDARY_CTRL;
    dev->slave = ATA_DEV_MASTER;
  }
  else if(ata_identify(ATA_SECONDARY_IO, ATA_DEV_SLAVE, dev))
  {
    dev->base = ATA_SECONDARY_IO;
    dev->ctrl = ATA_SECONDARY_CTRL;
    dev->slave = ATA_DEV_SLAVE;
  }
  else
  {

    dev->type = 0xFF;
  }
}
