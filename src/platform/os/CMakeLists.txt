# /*
#  * Copyright (c) 2019 Diego Asanza
#  * 
#  * SPDX-License-Identifier: Apache License 2.0
#  * 
#  * Created Date: Friday January 25th 2019
#  * Author: diego
#  */

# Directories of the vendor libraries.
set(FREERTOS_DIR "${CMAKE_CURRENT_LIST_DIR}/amazon-freertos")

#
# STM32 hal driver sources
#

set(FREERTOS_SOURCES
"${FREERTOS_DIR}/lib/FreeRTOS/event_groups.c"
"${FREERTOS_DIR}/lib/FreeRTOS/list.c"
"${FREERTOS_DIR}/lib/FreeRTOS/queue.c"
"${FREERTOS_DIR}/lib/FreeRTOS/stream_buffer.c"
"${FREERTOS_DIR}/lib/FreeRTOS/tasks.c"
"${FREERTOS_DIR}/lib/FreeRTOS/timers.c"
"${FREERTOS_DIR}/lib/FreeRTOS/portable/GCC/ARM_CM3/port.c"
# "${FREERTOS_DIR}/lib/FreeRTOS/portable/MemMang/heap_3.c"
)

set(FREERTOS_INCLUDES
"${FREERTOS_DIR}/lib/include"
"${FREERTOS_DIR}/lib/include/private"
"./"
"${FREERTOS_DIR}/lib/FreeRTOS/portable/GCC/ARM_CM3/"
)

set(OS_SOURCES
)

add_library(oslib
  ${FREERTOS_SOURCES}
  "${CMAKE_CURRENT_LIST_DIR}/src/os.c"  
  "${CMAKE_CURRENT_LIST_DIR}/src/queue.c"  
  "${CMAKE_CURRENT_LIST_DIR}/src/threads.c"  
  "${CMAKE_CURRENT_LIST_DIR}/src/syscalls.c"  
)

target_include_directories(oslib PRIVATE
    ${FREERTOS_INCLUDES}
)

target_include_directories(oslib PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_compile_options(oslib PRIVATE
    -Os
    -fomit-frame-pointer
    -fexpensive-optimizations
)

target_link_libraries(oslib archlib
"-Xlinker --wrap=malloc"
"-Xlinker --wrap=_malloc_r" 
)

target_compile_definitions(oslib PUBLIC
)
