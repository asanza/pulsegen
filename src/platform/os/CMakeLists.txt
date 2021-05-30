set(TARGET freertos)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/croutine.c
    ${CMAKE_CURRENT_LIST_DIR}/src/event_groups.c
    ${CMAKE_CURRENT_LIST_DIR}/src/list.c
    ${CMAKE_CURRENT_LIST_DIR}/src/queue.c
    ${CMAKE_CURRENT_LIST_DIR}/src/tasks.c
    ${CMAKE_CURRENT_LIST_DIR}/src/timers.c
    ${CMAKE_CURRENT_LIST_DIR}/portable/GCC/ARM_CM3/port.c
    ${CMAKE_CURRENT_LIST_DIR}/portable/MemMang/heap_1.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})
# target_link_libraries(cbor freertos hal)
target_include_directories(${TARGET} PRIVATE
)

target_include_directories(${TARGET} PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
  "${CMAKE_CURRENT_LIST_DIR}/portable/GCC/ARM_CM3"
  )

target_compile_options(${TARGET} PRIVATE -Wno-extra)
