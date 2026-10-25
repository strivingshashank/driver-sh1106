cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(sh1106 C CXX ASM)

pico_sdk_init()

add_executable(sh1106
        src/main.c
        src/log.c
        src/sh1106_core.c
)

target_link_libraries(sh1106
        pico_stdlib
        hardware_i2c
        pico_cyw43_arch_none
)

target_include_directories(sh1106 PRIVATE
        include
        # $(CMAKE_CURRENT_LIST_DIR)/include
)

pico_enable_stdio_usb(sh1106 1)
pico_enable_stdio_uart(sh1106 0)

pico_add_extra_outputs(sh1106)
