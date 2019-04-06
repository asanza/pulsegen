# /*
#  * Copyright (c) 2019 Diego Asanza
#  * 
#  * SPDX-License-Identifier: Apache License 2.0
#  * 
#  * Created Date: Friday January 25th 2019
#  * Author: diego
#  */

add_library(syslib
"${CMAKE_CURRENT_LIST_DIR}/sys_debug.c"  
# "${CMAKE_CURRENT_LIST_DIR}/evt.c"  
)

target_include_directories(syslib PRIVATE
)

target_include_directories(syslib PUBLIC
  "${PROJECT_SOURCE_DIR}/../include"
)

target_compile_options(syslib PRIVATE
)

target_compile_definitions(syslib PUBLIC
)

target_link_libraries(syslib archlib oslib 
)