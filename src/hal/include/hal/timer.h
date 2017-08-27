#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum timer_mode {
    HAL_TIMER_PULSE,
    HAL_TIMER_PWM
};

void timer_init( enum timer_mode mode );

void timer_stop( void );
void timer_start( void );

void timer_set_mode( enum timer_mode mode );

void timer_set_freq( int freq );
void timer_set_duty( int duty );

void timer_set_ton( int ton );
void timer_set_toff( int toff );
void timer_set_count( uint16_t count );


#ifdef __cplusplus
}
#endif

#endif
