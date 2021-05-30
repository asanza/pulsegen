set(TARGET sys)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/evt.c
    ${CMAKE_CURRENT_LIST_DIR}/src/syscalls.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(${TARGET} PRIVATE hal_stm32f1xx freertos)
