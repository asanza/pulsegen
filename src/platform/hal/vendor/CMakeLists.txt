set(TARGET hal_stm32f1xx)

set(${TARGET}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_eth.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_hcd.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2s.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_irda.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nand.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nor.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pccard.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sd.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_smartcard.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_wwdg.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_sdmmc.c
    ${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
)

add_library(${TARGET} ${${TARGET}_SOURCES})
# target_link_libraries(cbor freertos hal)
target_include_directories(${TARGET} PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Inc"
)

target_include_directories(${TARGET} PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include"
  "${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32F1xx/Include"
)

target_compile_options(${TARGET} PRIVATE -Wno-extra)
