
add_library(dev_lowlevel)
target_include_directories(dev_lowlevel PUBLIC include)
target_sources(dev_lowlevel 
    PUBLIC ${CMAKE_SOURCE_DIR}/src/dev_lowlevel.c
)
target_link_libraries(dev_lowlevel PRIVATE pico_stdlib)

add_library(bsp)
target_include_directories(bsp PUBLIC include)
target_sources(bsp PUBLIC ${CMAKE_SOURCE_DIR}/src/bsp.cpp)
target_link_libraries(bsp PRIVATE pico_stdlib hardware_resets hardware_irq)



add_executable(usbpro
        main.cpp 
)
target_link_libraries(usbpro PRIVATE pico_stdlib bsp dev_lowlevel pico_cyw43_arch_none)

# pull in common dependencies

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(usbpro)
# pico_add_extra_outputs(dev_lowlevel)

