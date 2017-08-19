#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include <stdint.h>

enum timer_mode {
    HAL_TIMER_SINGLE_PULSE,
    HAL_TIMER_PWM
};

struct hal_timer {
    uint32_t ton;
    uint32_t toff;
    uint32_t pwm_freq;
    uint32_t count;
    enum timer_mode mode;
};

void timer_init(struct hal_timer* timer);
void timer_stop( void );
void timer_start( void );

#endif
