
# set root directories.
set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(DEPLOY_FILE "${APP_DIR}/../../dist/display_node_${GIT_BRANCH}_${GIT_COMMIT_HASH}.hex")

set(APP_LINKER_SCRIPT "-Wl,-T${APP_DIR}/../arch/stm32f107/STM32F107RCTx_FLASH.ld")


set(APP_SOURCES
    "${APP_DIR}/main.c"
)


add_executable(app
    ${APP_SOURCES}
)

target_include_directories(app PRIVATE
)

target_link_libraries(app archlib oslib ${APP_LINKER_SCRIPT})

target_compile_options(app PRIVATE
)

add_custom_command(TARGET app POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex app ${APP_DIR}/../../dist/display_node_m31m_${GIT_VERSION}.hex)

add_custom_command(TARGET app POST_BUILD
    COMMAND arm-none-eabi-size --format=berkeley app
)
