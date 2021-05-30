set(target upg200)

set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/startup_stm32f107xc.s
)

add_executable(${target} ${sources})

target_link_libraries(${target} 
    -Xlinker -T${CMAKE_CURRENT_LIST_DIR}/STM32F107RCTx_FLASH.ld
    freertos
    hal
    sys
)
