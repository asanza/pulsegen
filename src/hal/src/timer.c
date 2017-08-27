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
static enum timer_mode mode;

extern uint32_t SystemCoreClock;

#define _PERIOD ( 100 + 1 )

static void get_pwm_reg_values(uint32_t freq, uint32_t duty, uint16_t* period,
		uint16_t* prescaler, uint16_t* pulse ) {
	uint32_t p;
	if( duty > 100 )
		duty = 100;
	*period = _PERIOD;
	*pulse = duty;
	p = ( SystemCoreClock * 1.0 ) / ( freq * _PERIOD * 1.0 ) - 1;
	if (p > 0xFFFF)
		*prescaler = 0xFFFF;
	else
		*prescaler = p;
}

static  uint16_t get_prescaler( uint32_t freq ) {
	uint32_t p;
	p = ( SystemCoreClock * 1.0 ) / ( freq * _PERIOD * 1.0 ) - 1;
	if (p > 0xFFFF)
		p = 0xFFFF;
	return p;
}

static void set_mode_pwm( uint32_t freq, uint32_t duty ) {

	TIM_ClockConfigTypeDef clk_src_cfg;
	TIM_MasterConfigTypeDef master_cfg;
	TIM_OC_InitTypeDef oc_cfg;

	uint16_t period, prescaler, pulse;

	get_pwm_reg_values( freq, duty, &period, &prescaler, &pulse );

	tim3.Instance = TIM3;
	tim3.Init.Prescaler = prescaler;
	tim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim3.Init.Period = period;
	tim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_ASSERT(HAL_TIM_Base_Init(&tim3)==HAL_OK);

	clk_src_cfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	clk_src_cfg.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
	HAL_ASSERT(HAL_TIM_ConfigClockSource(&tim3, &clk_src_cfg)==HAL_OK);


	HAL_ASSERT(HAL_TIM_PWM_Init(&tim3)==HAL_OK);
	HAL_ASSERT(HAL_TIM_OnePulse_Init(&tim3, TIM_OPMODE_REPETITIVE) == HAL_OK );

	master_cfg.MasterOutputTrigger = TIM_TRGO_RESET;
	master_cfg.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_ASSERT(HAL_TIMEx_MasterConfigSynchronization(&tim3, &master_cfg)==HAL_OK);

	oc_cfg.OCMode = TIM_OCMODE_PWM2;
	oc_cfg.Pulse = pulse;
	oc_cfg.OCPolarity = TIM_OCPOLARITY_LOW;
	oc_cfg.OCFastMode = TIM_OCFAST_ENABLE;
	HAL_ASSERT(HAL_TIM_PWM_ConfigChannel(&tim3, &oc_cfg, TIM_CHANNEL_3)==HAL_OK);

}

static void set_mode_pulse( uint32_t ton, uint32_t toff, uint32_t count ) {

	TIM_ClockConfigTypeDef clk_src_cfg;
	TIM_MasterConfigTypeDef master_cfg;
	TIM_OC_InitTypeDef oc_cfg;

	uint16_t period, prescaler, pulse;

	//get_pwm_reg_values( freq, duty, &period, &prescaler, &pulse );

	tim3.Instance = TIM3;
	tim3.Init.Prescaler = 2000;
	tim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	tim3.Init.Period = 1000;
	tim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_ASSERT(HAL_TIM_Base_Init(&tim3)==HAL_OK);

	clk_src_cfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	clk_src_cfg.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
	HAL_ASSERT(HAL_TIM_ConfigClockSource(&tim3, &clk_src_cfg)==HAL_OK);


	HAL_ASSERT(HAL_TIM_OC_Init(&tim3)==HAL_OK);
	HAL_ASSERT(HAL_TIM_OnePulse_Init(&tim3, TIM_OPMODE_SINGLE) == HAL_OK );

	master_cfg.MasterOutputTrigger = TIM_TRGO_RESET;
	master_cfg.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_ASSERT(HAL_TIMEx_MasterConfigSynchronization(&tim3, &master_cfg)==HAL_OK);

	oc_cfg.OCMode = TIM_OCMODE_TOGGLE;
	oc_cfg.Pulse = 500;
	oc_cfg.OCPolarity = TIM_OCPOLARITY_LOW;
	HAL_ASSERT(HAL_TIM_OC_ConfigChannel(&tim3, &oc_cfg, TIM_CHANNEL_3)==HAL_OK);

}

void timer_init( enum timer_mode _mode )
{

	mode = _mode;

	GPIO_InitTypeDef gpio_init_struct;

	HAL_NVIC_SetPriority(TIM3_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	gpio_init_struct.Pull  = GPIO_PULLDOWN;
	gpio_init_struct.Mode  = GPIO_MODE_AF_OD;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init_struct.Pin   = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOC, &gpio_init_struct);

	if( mode == HAL_TIMER_PWM ) {
		set_mode_pwm (1000, 20);
	} else {
		set_mode_pulse(100, 100, 1);
	}

	__HAL_AFIO_REMAP_TIM3_ENABLE();

}

void timer_set_freq(int freq) {
	if( mode != HAL_TIMER_PWM )
		return;
	__HAL_TIM_PRESCALER( &tim3, get_prescaler( freq ) );
}

void timer_set_duty( int duty ) {
	__HAL_TIM_SetCompare(&tim3, TIM_CHANNEL_3, duty);
}

void timer_start( void ) {
	if( mode == HAL_TIMER_PWM )
		HAL_TIM_PWM_Start(&tim3, TIM_CHANNEL_3);
	else
		HAL_TIM_OC_Start(&tim3, TIM_CHANNEL_3);
}

void timer_stop( void ) {
	if( mode == HAL_TIMER_PWM )
		HAL_TIM_PWM_Stop(&tim3, TIM_CHANNEL_3);
	else
		HAL_TIM_OC_Stop(&tim3, TIM_CHANNEL_3);
}

void timer_set_count( uint16_t count ) {

}

void timer_set_mode( enum timer_mode mode ) {
	timer_stop();
	if( mode == HAL_TIMER_PWM ) {
		HAL_TIM_PWM_DeInit(&tim3);
		set_mode_pwm(1000, 10);
	} else {
		HAL_TIM_OC_DeInit(&tim3);
		set_mode_pulse(100, 100, 1);
	}
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim3);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {

}
