#include <sfs.h>
#include <memory>
#include <disk.h>
#include <ATA.h>

export "C"{


SuperBlock loadSuperBlock(struct ata_device *dev,uint8_t buffer)
{
  SuperBlock block;
  
  find_partition_start_lba(&dev,0x6e);
  block.last_off_set = find_partition_last_lba(&dev,0x6e);
  

  return block;
  
}
  
}
