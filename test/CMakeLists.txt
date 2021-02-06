add_executable(test
        test.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(test pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(test 0)
pico_enable_stdio_uart(test 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(test)

# add url via pico_set_program_url
example_auto_set_url(test)

add_custom_command(TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/../copy.ps1"
        $<TARGET_FILE_DIR:test>)