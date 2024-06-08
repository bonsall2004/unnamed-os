cmake_minimum_required(VERSION 3.10)
project(custom_os)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

add_subdirectory(src/kernel)

add_custom_target(everything ALL DEPENDS bootloader)

add_custom_target(clean-binaries ALL
                  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  COMMENT "Cleaning binaries directory"
                  )

set(OUTPUT_BINARIES
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    )
set(OUTPUT_DISK_NAME bootable)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_custom_target(bootable_image
                    COMMAND rm -f ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd
                    COMMAND truncate -s 67108864 ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd
                    COMMAND sgdisk ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd -n 1:2048 -t 1:ef00
                    COMMAND ${CMAKE_SOURCE_DIR}/deps/limine/limine bios-install ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd
                    COMMAND mformat -i ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd@@1M
                    COMMAND mmd -i ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine
                    COMMAND mcopy -i ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd@@1M ${CMAKE_SOURCE_DIR}/binaries/kernel ::/boot
                    COMMAND mcopy -i ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd@@1M ${CMAKE_SOURCE_DIR}/deps/limine/limine.cfg ${CMAKE_SOURCE_DIR}/deps/limine/limine-bios.sys ::/boot/limine
                    COMMAND mcopy -i ${CMAKE_SOURCE_DIR}/${OUTPUT_DISK_NAME}.hdd@@1M ${CMAKE_SOURCE_DIR}/deps/limine/BOOTX64.EFI ::/EFI/BOOT
                    COMMENT "Building bootloader and creating bootable.img"
                    DEPENDS kernel
                    )
  endif()