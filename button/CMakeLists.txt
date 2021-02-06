add_executable(button
        button.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(button pico_stdlib pico_multicore)

# enable usb output, disable uart output
pico_enable_stdio_usb(button 0)
pico_enable_stdio_uart(button 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(button)

# add url via pico_set_program_url
example_auto_set_url(button)

add_custom_command(TARGET button POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/../copy.ps1"
        $<TARGET_FILE_DIR:button>)