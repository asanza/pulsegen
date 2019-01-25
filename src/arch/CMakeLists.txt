# /*
#  * Copyright (c) 2019 Diego Asanza
#  * 
#  * SPDX-License-Identifier: Apache License 2.0
#  * 
#  * Created Date: Friday January 25th 2019
#  * Author: diego
#  */

# Directories of the vendor libraries.
set(STM32F1xx_HAL_DIR "${CMAKE_CURRENT_LIST_DIR}/support/STM32F1xx_HAL_Driver")
set(CMSIS_DIR "${CMAKE_CURRENT_LIST_DIR}/support/CMSIS")

#
# STM32 hal driver sources
#

set(STM_HAL_DRIVERS
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_adc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_adc_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_can.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_cec.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_cortex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_crc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_dac.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_dac_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_dma.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_eth.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_flash.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_flash_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_gpio.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_gpio_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_hcd.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_i2c.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_i2s.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_irda.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_iwdg.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_mmc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_nand.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_nor.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_pccard.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_pcd.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_pcd_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_pwr.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_rcc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_rcc_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_rtc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_rtc_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_sd.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_smartcard.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_spi.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_spi_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_sram.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_tim.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_tim_ex.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_uart.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_usart.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_hal_wwdg.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_adc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_crc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_dac.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_dma.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_exti.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_fsmc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_gpio.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_i2c.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_pwr.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_rcc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_rtc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_sdmmc.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_spi.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_tim.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_usart.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_usb.c"
"${STM32F1xx_HAL_DIR}/Src/stm32f1xx_ll_utils.c"
)

set(STM_HAL_DRIVER_INCLUDES
"${STM32F1xx_HAL_DIR}/Inc"
"${CMSIS_DIR}/Device/ST/STM32F1xx/Include"
"${CMSIS_DIR}/Include"
"stm32f1xx/"
)

set(BASELIB_SOURCES
    ${STM_HAL_DRIVERS}
    # "${CMAKE_CURRENT_LIST_DIR}/stm32f1xx/hal_sys.c"
)

add_library(archlib
    ${BASELIB_SOURCES}
)

target_include_directories(archlib PRIVATE
    ${STM_HAL_DRIVER_INCLUDES}
)

target_compile_options(archlib PRIVATE
    -Os
    -fomit-frame-pointer
    -fexpensive-optimizations
)

target_compile_definitions(archlib PUBLIC
  STM32F107xC
)
