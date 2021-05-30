set(target upg200)

set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

add_executable(${target} ${sources})

target_link_libraries(${target} 
    -Xlinker -specs=nano.specs
    freertos
    sys
)
