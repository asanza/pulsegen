#include <hal/timer.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include <hal/gpio.h>
#include <hal/error.h>

#define DEFAULT_FREQ
#define DEFAULT_DUTY
#define DEFAULT_COUNT 	1
#define DEFAULT_TON
#define DEFAULT_TOFF

static TIM_HandleTypeDef tim3;

static set_mode_pwm( uint32_t freq, uint32_t duty ) {

	TIM_ClockConfigTypeDef clk_src_cfg;
	TIM_MasterConfigTypeDef master_cfg;
	TIM_OC_InitTypeDef oc_cfg;

	timer_stop();

	tim3.Init.Prescaler = freq;

}

static set_mode_pulse( uint32_t ton, uint32_t toff, uint32_t count ) {

}

void timer_init( enum timer_mode mode )
{
	TIM_ClockConfigTypeDef clk_src_cfg;
	TIM_MasterConfigTypeDef master_cfg;
	TIM_OC_InitTypeDef oc_cfg;

	GPIO_InitTypeDef gpio_init_struct;

	HAL_NVIC_SetPriority(TIM3_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	__HAL_RCC_TIM3_CLK_ENABLE();

	tim3.Instance = TIM3;
	tim3.Init.Prescaler = 0;
	tim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim3.Init.Period = 1;
	tim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_ASSERT(HAL_TIM_Base_Init(&tim3)==HAL_OK);

	clk_src_cfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	clk_src_cfg.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
	HAL_ASSERT(HAL_TIM_ConfigClockSource(&tim3, &clk_src_cfg)==HAL_OK);

	HAL_ASSERT(HAL_TIM_OC_Init(&tim3)==HAL_OK);

	HAL_ASSERT(HAL_TIM_OnePulse_Init(&tim3, TIM_OPMODE_REPETITIVE) == HAL_OK );

	master_cfg.MasterOutputTrigger = TIM_TRGO_RESET;
	master_cfg.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_ASSERT(HAL_TIMEx_MasterConfigSynchronization(&tim3, &master_cfg)==HAL_OK);

	oc_cfg.OCMode = TIM_OCMODE_PWM2;
	oc_cfg.Pulse = 1;
	oc_cfg.OCPolarity = TIM_OCPOLARITY_LOW;
	oc_cfg.OCFastMode = TIM_OCFAST_ENABLE;
	HAL_ASSERT(HAL_TIM_PWM_ConfigChannel(&tim3, &oc_cfg, TIM_CHANNEL_3)==HAL_OK);

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	gpio_init_struct.Pull  = GPIO_PULLDOWN;
	gpio_init_struct.Mode  = GPIO_MODE_AF_OD;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init_struct.Pin   = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOC, &gpio_init_struct);
	__HAL_AFIO_REMAP_TIM3_ENABLE();
}

void timer_start( void ) {
	HAL_ASSERT(HAL_TIM_PWM_Start(&tim3, TIM_CHANNEL_3) == HAL_OK);
}

void timer_stop( void ) {
	HAL_ASSERT( HAL_TIM_PWM_Stop(&tim3, TIM_CHANNEL_3) == HAL_OK );
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim3);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {

}
