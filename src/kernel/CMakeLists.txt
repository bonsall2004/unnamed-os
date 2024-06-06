project(kernel C)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)
set(C_SOURCES
    ${SRC_DIR}/main.c
    )

add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    COMMAND ${CMAKE_C_COMPILER} -c ${C_SOURCES} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.o
    COMMAND ${CMAKE_LINKER} -T ${CMAKE_SOURCE_DIR}/src/linker_scripts/link-64.ld -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.o
    DEPENDS ${C_SOURCES}
    COMMENT "Building kernel"
    )

add_custom_target(kernel ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin)
