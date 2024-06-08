cmake_minimum_required(VERSION 3.10)
project(custom_os)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

add_subdirectory(src/bootloader)
add_subdirectory(src/kernel)

add_custom_target(everything ALL DEPENDS bootloader)

add_custom_target(clean-binaries ALL
                  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                  COMMENT "Cleaning binaries directory"
                  )

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_custom_target(bootable_image
                    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target bootloader
                    COMMAND cat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stage1.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stage2.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin > ${CMAKE_SOURCE_DIR}/bootable.img
                    COMMAND truncate -s 1474560 ${CMAKE_SOURCE_DIR}/bootable.img
                    COMMENT "Building bootloader and creating bootable.img"
                    DEPENDS bootloader kernel
                    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_custom_target(bootable_image
                    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target bootloader
                    COMMAND cat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stage1.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stage2.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin > ${CMAKE_SOURCE_DIR}/bootable.img
                    COMMAND fsutil file seteof ${CMAKE_SOURCE_DIR}/bootable.img 1474560
                    COMMENT "Building bootloader and creating bootable.img"
                    DEPENDS bootloader kernel
                    )
endif ()
