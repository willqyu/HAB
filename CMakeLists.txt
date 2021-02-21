cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico)

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

add_executable(pico
    main.c
    misc.c
    sensors/bmp.c
    )

target_link_libraries(pico 
    pico_stdlib 
    pico_multicore
    pico_sync
    hardware_spi 
    hardware_i2c 
    hardware_adc
)

pico_add_extra_outputs(
    pico
)