set(TARGET ssd1351)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ssd1351.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(${TARGET} PRIVATE hal_stm32f1xx)
