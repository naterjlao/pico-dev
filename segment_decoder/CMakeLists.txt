add_executable(segment_decoder
        segment_decoder.c
        )

# pull in common dependencies
target_link_libraries(segment_decoder pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(segment_decoder)

