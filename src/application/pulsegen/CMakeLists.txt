set(target upg200)

set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    # ${CMAKE_CURRENT_LIST_DIR}/src/pgen.cc
    ${CMAKE_CURRENT_LIST_DIR}/startup_stm32f107xc.s
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/STM32F107RCTx_FLASH.ld CACHE INTERNAL "LINKER_SCRIPT")

add_executable(${target}.elf ${sources})

target_link_libraries(${target}.elf
    -Xlinker -T${LINKER_SCRIPT}
    -Xlinker -Map=${target}.map
    -Wl,--whole-archive
    freertos
    ssd1351
    hal
    sys
    ugui
    -Wl,--no-whole-archive
)

set_target_properties(${target}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_target(${target}_${GIT_VERSION}.hex COMMAND 
    ${CMAKE_OBJCOPY} -O ihex ${target}.elf ${PROJECT_SOURCE_DIR}/dist/${target}_${GIT_VERSION}.hex
    DEPENDS ${target}.elf
)
