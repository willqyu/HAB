add_executable(thread
        thread.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(thread pico_stdlib pico_multicore)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(thread)

# add url via pico_set_program_url
example_auto_set_url(thread)
