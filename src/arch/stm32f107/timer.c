#include <hal/timer.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include <hal/gpio.h>
#include <hal/error.h>

#define DEFAULT_FREQ	1000
#define DEFAULT_DUTY	50
#define DEFAULT_COUNT 	1
#define MIN_TON			1
#define MIN_TOFF		1
#define MAX_TON			9999999
#define MAX_TOFF		9999999
#define MAX_PULSE_COUNT 9999
#define MIN_PULSE_COUNT 1
#define _PERIOD ( 100 + 1 )

extern uint32_t SystemCoreClock;


struct timer_config {
	uint32_t frequency;
	uint32_t count;
	uint32_t duty;
	uint32_t ton;
	uint32_t toff;
	enum timer_mode mode;
};

static struct timer_config config = {
	.frequency = DEFAULT_FREQ,
	.count = MIN_PULSE_COUNT,
	.duty =	DEFAULT_DUTY,
	.ton = MIN_TON,
	.toff = MIN_TOFF,
	.mode = HAL_TIMER_PWM
};

static  uint16_t get_prescaler( uint32_t freq ) {
	uint32_t p;
	p = ( SystemCoreClock * 1.0 ) / ( freq * _PERIOD * 1.0 ) - 1;
	if (p > 0xFFFF) {
		p = 0xFFFF;
	}
	return p;
}

static uint32_t get_frequency( uint16_t prescaler ) {
	uint32_t freq = SystemCoreClock * 1.0 / ( _PERIOD * ( prescaler + 1 ) * 1.0 );
	return freq;
}

uint32_t timer_get_freq( void ) {
	return config.frequency;
}



static void set_mode_pwm( struct timer_config* config ) {

	uint16_t prescaler = get_prescaler( config->frequency );
	config->frequency = get_frequency(prescaler);

	TIM3->PSC = prescaler; /* prescaler */
	TIM3->ARR = _PERIOD;

	TIM3->CCR3 = config->duty;

	TIM3->CR1 &= ~TIM_CR1_CKD;
	TIM3->CR1 |= TIM_CLOCKDIVISION_DIV1;
	TIM3->CR1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
	TIM3->CR1 |= TIM_COUNTERMODE_UP;

	TIM3->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM3->CCMR2 &= ~TIM_CCMR2_CC3S;
	TIM3->CCMR2 |= TIM_OCMODE_PWM1;
	TIM3->SMCR |= TIM_SMCR_TS_0;
	TIM3->SMCR |= (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0);

	TIM3->CR1 &= ~TIM_CR1_OPM;

	TIM2->PSC = 0;
	TIM2->ARR = 0xFFFE;
	TIM2->CCR3 = 0;
	TIM2->CR1 |= TIM_CLOCKDIVISION_DIV1;
	TIM2->CR1 |= TIM_COUNTERMODE_UP;

	TIM2->CR2 |= TIM_CR2_MMS_1;

}

static void set_mode_pulse( struct timer_config* config ) {

}

static void init_hw(struct timer_config* config) {
	GPIO_InitTypeDef gpio_init_struct;
	HAL_NVIC_SetPriority(TIM3_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	HAL_NVIC_SetPriority(TIM2_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	gpio_init_struct.Pull  = GPIO_PULLDOWN;
	gpio_init_struct.Mode  = GPIO_MODE_AF_OD;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init_struct.Pin   = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOC, &gpio_init_struct);

	if( config->mode == HAL_TIMER_PWM ) {
		set_mode_pwm (config);
	} else {
		set_mode_pulse(config);
	}

	__HAL_AFIO_REMAP_TIM3_ENABLE();
}


void timer_start( void ) {
	if( config.mode == HAL_TIMER_PWM ) {
		TIM2->CR1 |= TIM_CR1_CEN;
		TIM3->CCER |= TIM_CCER_CC3E;	/* output enable */
		TIM3->CR1 |= TIM_CR1_CEN;
	} else {
//		HAL_TIM_OC_Start(&tim3, TIM_CHANNEL_3);
	}
}

void timer_init( enum timer_mode _mode )
{
	config.mode = _mode;
	init_hw(&config);
}

void timer_set_freq(int freq) {
	if( config.mode != HAL_TIMER_PWM )
		return;
	if( config.frequency == freq ) return;
	if( freq < 10 ) return;
	uint16_t prescaler = get_prescaler( freq );
	if ( prescaler == get_prescaler( config.frequency ) ) {
		if( freq > config.frequency )
		{
			if(prescaler != 0) prescaler--;
		} else {
			if(prescaler != 0xFFFF) prescaler++;
		}
	}
	TIM3->PSC = prescaler;
	config.frequency = get_frequency( prescaler );
}

void timer_set_duty( int duty ) {
	if( config.mode != HAL_TIMER_PWM ) {
		return;
	}
	if(duty < 1 && duty > 99) {
		return;
	}
	config.duty = duty;
}


void timer_stop( void ) {
	if( config.mode == HAL_TIMER_PWM ) {
		TIM3->CCER &= ~TIM_CCER_CC3E;	/* output enable */
		TIM3->CR1 &= ~TIM_CR1_CEN;
	} else {
	}
}

void timer_set_count( uint32_t _count ) {
	if(_count >= MAX_PULSE_COUNT|| _count < MIN_PULSE_COUNT) {
		return;
	}
	config.count = _count;
}

uint32_t timer_get_count( void ) {
	return config.count;
}

void timer_set_mode( enum timer_mode _mode ) {
	timer_stop();
	config.mode = _mode;
	if( _mode == HAL_TIMER_PWM ) {
		set_mode_pwm(&config);
	} else {
		set_mode_pulse(&config);
	}
}

void timer_set_ton(int value) {
	if(value > MAX_TON|| value < MIN_TON) {
		return;
	}
	config.ton = value;
}

void timer_set_toff(int value) {
	if(value > MAX_TOFF || value < MIN_TOFF) {
		return;
	}
	config.toff = value;
}


int timer_get_ton(void) {
	return config.ton;
}

int timer_get_toff(void) {
	return config.toff;
}

void TIM3_IRQHandler(void)
{
}

void TIM2_IRQHandler( void ) {
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {

}
