#include <sfs.h>
#include <memory>
#include <disk.h>
#include <ATA.h>

export "C"{


SuperBlock loadSuperBlock(struct ata_device *dev, uint8_t *buffer)
{
    SuperBlock block;

    read_between_lbams(dev,
                       find_partition_start_lba(dev, 0x6e),
                       find_partition_last_lba(dev, 0x6e),
                       buffer);

    size_t offset = 0;

    memcpy(&block.num_block, buffer + offset, sizeof(block.num_block));
    offset += sizeof(block.num_block);

    memcpy(&block.num_inods, buffer + offset, sizeof(block.num_inods));
    offset += sizeof(block.num_inods);

    memcpy(&block.data_block_start, buffer + offset, sizeof(block.data_block_start));
    offset += sizeof(block.data_block_start);

    memcpy(&block.data_block_size, buffer + offset, sizeof(block.data_block_size));
    offset += sizeof(block.data_block_size);

    memcpy(&block.blocker_point, buffer + offset, sizeof(block.blocker_point));
    offset += sizeof(block.blocker_point);

    memcpy(&block.size_of_index, buffer + offset, sizeof(block.size_of_index));

    return block;
}
  
}
