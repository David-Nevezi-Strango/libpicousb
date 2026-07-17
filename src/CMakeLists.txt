add_executable(usbpro
        main.cpp 
)
add_library(dev_lowlevel)
target_include_directories(dev_lowlevel PUBLIC include)
target_sources(dev_lowlevel 
    PUBLIC ${CMAKE_SOURCE_DIR}/src/dev_lowlevel.c
)

target_link_libraries(dev_lowlevel PRIVATE pico_stdlib)
target_link_libraries(usbpro PRIVATE pico_stdlib hardware_resets hardware_irq dev_lowlevel pico_cyw43_arch_none)

# pull in common dependencies

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(usbpro)
# pico_add_extra_outputs(dev_lowlevel)

