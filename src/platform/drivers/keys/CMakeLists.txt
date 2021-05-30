set(TARGET keybd)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/keybd.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(${TARGET} PRIVATE hal_stm32f1xx)
