add_executable(segments_decoder
        segments_decoder.c
        )

# pull in common dependencies
target_link_libraries(segments_decoder pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(segments_decoder)

