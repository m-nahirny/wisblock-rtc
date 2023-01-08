cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(wisblock_rtc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(wisblock_rtc
        wisblock_rtc.c
        RV3028.c
)

pico_enable_stdio_usb(wisblock_rtc 0)
pico_enable_stdio_uart(wisblock_rtc 1)
        
# create map/bin/hex file etc.
pico_add_extra_outputs(wisblock_rtc)

# add url via pico_set_program_url
#example_auto_set_url(blink)

# pull in common dependencies
target_link_libraries(wisblock_rtc pico_stdlib hardware_i2c)
