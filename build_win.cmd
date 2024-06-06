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

echo Creating empty disk image...
fsutil file createnew %IMAGE_FILE% 1474560

echo Write the bootloader to the first sector of the disk image...
copy /b /y %BOOTLOADER_FILE% %IMAGE_FILE%

echo Adding padding to the disk image to fill it up to 1.44MB (2880 sectors)...
fsutil file seteof %IMAGE_FILE% 1474560

echo Bootable disk image created: %IMAGE_FILE%

endlocal
