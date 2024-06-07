#!/bin/bash


set -e

# Define variables
BINARIES_FOLDER="binaries"
BOOTLOADER_FILE="$BINARIES_FOLDER/bootloader/stage1.bin"
IMAGE_FILE="bootable_disk.img"


mkdir -p intermediate/debug/x64


cd intermediate/debug/x64


cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" ../../../
ninja all


cd ../../../

echo "Creating empty disk image..."
dd if=/dev/zero of="$IMAGE_FILE" bs=512 count=2880

echo "Write the bootloader to the first sector of the disk image..."
dd if="$BOOTLOADER_FILE" of="$IMAGE_FILE" conv=notrunc

echo "Bootable disk image created: $IMAGE_FILE"
