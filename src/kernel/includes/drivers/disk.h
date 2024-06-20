/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include <cstdint>
#include <cstdio>

#define HBA_PORT_DEV_PRESENT 0x3
#define HBA_PORT_IPM_ACTIVE  0x1
#define ATA_CMD_READ_DMA_EX  0x25

struct HBAPort {
  uint32_t clb;    // Command list base address, 1K-byte aligned
  uint32_t clbu;   // Command list base address upper 32 bits
  uint32_t fb;     // FIS base address, 256-byte aligned
  uint32_t fbu;    // FIS base address upper 32 bits
  uint32_t is;     // Interrupt status
  uint32_t ie;     // Interrupt enable
  uint32_t cmd;    // Command and status
  uint32_t reserved0;
  uint32_t tfd;    // Task file data
  uint32_t sig;    // Signature
  uint32_t ssts;   // SATA status (SCR0:SStatus)
  uint32_t sctl;   // SATA control (SCR2:SControl)
  uint32_t serr;   // SATA error (SCR1:SError)
  uint32_t sact;   // SATA active (SCR3:SActive)
  uint32_t ci;     // Command issue
  uint32_t sntf;   // SATA notification (SCR4:SNotification)
  uint32_t fbs;    // FIS-based switch control
  uint32_t reserved1[11];
  uint32_t vendor[4];
};

struct FISRegH2D {
  uint8_t  fis_type;
  uint8_t  pmport:4;
  uint8_t  rsv0:3;
  uint8_t  c:1;
  uint8_t  command;
  uint8_t  featurel;
  uint8_t  lba0;
  uint8_t  lba1;
  uint8_t  lba2;
  uint8_t  device;
  uint8_t  lba3;
  uint8_t  lba4;
  uint8_t  lba5;
  uint8_t  featureh;
  uint16_t count;
  uint8_t  icc;
  uint8_t  control;
  uint32_t rsv1;
};

struct HBAPrtdEntry {
  uint32_t dsba;    // Data base address
  uint32_t dsbau;   // Data base address upper 32 bits
  uint32_t reserved0;
  uint32_t dbc:22;  // Byte count, 4M max
  uint32_t reserved1:9;
  uint32_t i:1;     // Interrupt on completion
};

struct HBACmdHeader {
  uint8_t  cfl:5;   // Command FIS length in DWORDS, 2 ~ 16
  uint8_t  a:1;     // ATAPI
  uint8_t  w:1;     // Write, 1: H2D, 0: D2H
  uint8_t  p:1;     // Prefetchable
  uint8_t  r:1;     // Reset
  uint8_t  b:1;     // BIST
  uint8_t  c:1;     // Clear busy upon R_OK
  uint8_t  rsv0:1;
  uint8_t  pmp:4;   // Port multiplier port
  uint16_t prdtl;   // Physical region descriptor table length in entries
  volatile uint32_t prdbc;    // Physical region descriptor byte count transferred
  uint32_t ctba;    // Command table descriptor base address
  uint32_t ctbau;   // Command table descriptor base address upper 32 bits
  uint32_t reserved1[4];
};

struct HBACmdTable {
  FISRegH2D cfis;     // Command FIS
  uint8_t acmd[16];   // ATAPI command
  uint8_t reserved[48];
  HBAPrtdEntry prdt_entry[1];  // Physical region descriptor table entries
};


class AHCI {
public:
  static void readFromDisk(HBAPort *port, uint64_t startSector, uint32_t sectorCount, void *buffer) {
      port->is = static_cast<uint32_t>(-1);  // Clear pending interrupt bits

      auto *cmdHeader = reinterpret_cast<HBACmdHeader*>(port->clb);
      cmdHeader->cfl = sizeof(FISRegH2D) / sizeof(uint32_t);  // Command FIS size
      cmdHeader->w = 0;    // Read from device
      cmdHeader->prdtl = 1;  // PRDT entries count

      auto *cmdTable = reinterpret_cast<HBACmdTable*>(cmdHeader->ctba);
      std::memset(cmdTable, 0, sizeof(HBACmdTable) + (cmdHeader->prdtl - 1) * sizeof(HBAPrtdEntry));

      cmdTable->prdt_entry[0].dsba = reinterpret_cast<uint32_t>(buffer);
      cmdTable->prdt_entry[0].dbc = (sectorCount << 9) - 1;    // 512 bytes per sector
      cmdTable->prdt_entry[0].i = 1;

      auto *cmdFis = &cmdTable->cfis;

      cmdFis->fis_type = 0x27;    // FIS_TYPE_REG_H2D
      cmdFis->c = 1;    // Command
      cmdFis->command = ATA_CMD_READ_DMA_EX;

      cmdFis->lba0 = static_cast<uint8_t>(startSector);
      cmdFis->lba1 = static_cast<uint8_t>(startSector >> 8);
      cmdFis->lba2 = static_cast<uint8_t>(startSector >> 16);
      cmdFis->device = 1 << 6;    // LBA mode

      cmdFis->lba3 = static_cast<uint8_t>(startSector >> 24);
      cmdFis->lba4 = static_cast<uint8_t>(startSector >> 32);
      cmdFis->lba5 = static_cast<uint8_t>(startSector >> 40);

      cmdFis->count = sectorCount;

      while (port->tfd & (0x80 | 0x08));  // Wait until not busy

      port->ci = 1;    // Issue command

      while (true) {
          if (!(port->ci & 1)) break;
          if (port->is & (1 << 30)) {
              printf("Task file error\n");
              return;  // Task file error
          }
        }
    }
};

