cmake_minimum_required(VERSION 3.20)
project(bootloader LANGUAGES NONE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

add_subdirectory(stage1)
add_subdirectory(stage2)

add_custom_target(bootloader ALL
                  DEPENDS stage1_bin stage2_bin
                  )