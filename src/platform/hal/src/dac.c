#include <hal/dac.h>
#include "stm32f1xx_hal.h"

static DAC_HandleTypeDef dac;

void dac_init(uint32_t val)
{
	DAC_ChannelConfTypeDef cfg;

	dac.Instance = DAC;

	HAL_DAC_Init(&dac);

	cfg.DAC_Trigger = DAC_TRIGGER_NONE;
	cfg.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&dac, &cfg, DAC_CHANNEL_1);
    HAL_DAC_Start(&dac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&dac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, val);
}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_DAC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void dac_set(uint32_t value)
{
	HAL_DAC_SetValue(&dac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
}
