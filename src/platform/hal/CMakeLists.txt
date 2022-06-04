add_subdirectory(vendor)

set(TARGET hal)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/dac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/error.c
    ${CMAKE_CURRENT_LIST_DIR}/src/gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/src/haltim.c
    ${CMAKE_CURRENT_LIST_DIR}/src/privfn.h
    ${CMAKE_CURRENT_LIST_DIR}/src/system_stm32f1xx.c
    ${CMAKE_CURRENT_LIST_DIR}/src/timer.c
    ${CMAKE_CURRENT_LIST_DIR}/src/uart.c
    ${CMAKE_CURRENT_LIST_DIR}/vendor/embedd/src/cmsis_nvic.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(${TARGET} PRIVATE hal_stm32f1xx)
