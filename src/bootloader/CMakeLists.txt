project(bootloader LANGUAGES NONE)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

set(SOURCES
    ${SRC_DIR}/entry.asm
    )

add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin
    COMMAND nasm -f bin ${SOURCES} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin
    DEPENDS ${SOURCES}
    COMMENT "Assembling bootloader"
    )

add_custom_target(bootloader ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin)
