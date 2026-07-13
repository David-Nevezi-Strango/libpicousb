add_executable(usbpro
        main.cpp
)

# pull in common dependencies
target_link_libraries(usbpro pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(usbpro)

# # call pico_set_program_url to set path to example on github, so users can find the source for an example via picotool
# example_auto_set_url(usbpro)
