set(TARGET boot)

set(${TARGET}_SOURCES
"${CMAKE_CURRENT_LIST_DIR}/src/boot.c"
)

add_library(${TARGET} ${${TARGET}_SOURCES} )

target_link_libraries(${TARGET} PRIVATE hal crc)

target_include_directories(${TARGET} PRIVATE
"${CMAKE_CURRENT_LIST_DIR}/src"
"${PLATFORM_INCLUDES}"
)

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
  )
