@echo off
setlocal

set BINARIES_FOLDER=binaries
set BOOTLOADER_FILE=%BINARIES_FOLDER%\bootloader\stage1.bin
set IMAGE_FILE=bootable_disk.img

if not exist intermediate (
    mkdir intermediate
)
if not exist intermediate\debug (
    mkdir intermediate\debug
)
if not exist intermediate\debug\x64 (
    mkdir intermediate\debug\x64
)

cd intermediate\debug\x64
cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" ..\..\..
ninja all
cd ..\..\..

"c:\program files\qemu\qemu-system-x86_x64.exe" -drive format=raw,file=bootable.img --no-reboot --no-shutdown --monitor stdio

endlocal