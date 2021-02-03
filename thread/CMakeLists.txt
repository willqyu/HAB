add_executable(thread
        thread.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(thread pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(thread 1)
pico_enable_stdio_uart(thread 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(thread)

# add url via pico_set_program_url
example_auto_set_url(thread)
