cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(major-project C CXX ASM)

pico_sdk_init()

add_executable(major-project
        src/sh1106_i2c
        src/ssd1306.c
        src/main.c
        src/onboard_led.c
)

target_link_libraries(major-project
        pico_stdlib
        hardware_i2c
        pico_cyw43_arch_none
)

target_include_directories(major-project PRIVATE
        include
        # $(CMAKE_CURRENT_LIST_DIR)/include
)

pico_enable_stdio_usb(major-project 1)
pico_enable_stdio_uart(major-project 0)

pico_add_extra_outputs(major-project)
