set(TARGET ugui)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ugui.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}"
)
