add_executable(shift_segments
        shift_segments.c
        )

# pull in common dependencies
target_link_libraries(shift_segments pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(shift_segments)

