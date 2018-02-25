#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>
#include <sys/evt.h>

#define START_LEVEL 330
#define MIN_LEVEL   150
#define MAX_LEVEL   620
#define START_FREQ  1000
#define START_DUTY  50
#define MAX_DUTY    99
#define MIN_DUTY    1

#define INTERN_LEVEL( x ) ( ( x - 0.5719 * 1.0 ) / 0.1647 )

PulseGenerator::PulseGenerator() {
    dac_init(INTERN_LEVEL(START_LEVEL));
    timer_init( HAL_TIMER_PWM );
    timer_set_freq( START_FREQ );
    timer_set_duty( START_DUTY );
    started = false;
    level = START_LEVEL;
    duty = START_DUTY;
    mode = PWM;
    ton = timer_get_ton();
    toff = timer_get_toff();
    count = timer_get_count();
}

void PulseGenerator::setMode(Mode mode) {
    this->mode = mode;
}

PulseGenerator::Mode PulseGenerator::getMode( void ) {
    return mode;
}

PulseGenerator::Mode PulseGenerator::toggleMode( void ) {
    stop();
    if(mode == PULSE) {
        mode = PWM;
        timer_set_mode(HAL_TIMER_PWM);
        timer_set_duty(duty);
    } else {
        timer_set_mode(HAL_TIMER_PULSE);
        timer_set_duty(duty);
        timer_set_count( count );
        mode = PULSE;
    }
    return mode;
}

void PulseGenerator::setTonFreq( int value ) {
   switch(mode) {
       case PWM:
            timer_set_freq( value );
            break;
       case PULSE:
    	   timer_set_ton( value );
   }
}

int PulseGenerator::getTonFreq() {
    switch(mode) {
        case PWM: return timer_get_freq();
        case PULSE: return timer_get_ton();
    }
    return 0;
}

void PulseGenerator::setLevel(int level) {
    if( level > MAX_LEVEL ) level = MAX_LEVEL;
    if( level < MIN_LEVEL ) level = MIN_LEVEL;
    this->level = level;
    dac_set(INTERN_LEVEL(level));
}

int PulseGenerator::getLevel() {
    return level;
}

int PulseGenerator::getToffDuty() {
    switch(mode) {
        case PWM: return duty;
        case PULSE: return timer_get_toff();
    }
    return 0;
}

void PulseGenerator::setToffDuty(int val) {
    switch(mode) {
        case PWM:
            if( val < MIN_DUTY )
                val = MIN_DUTY;
            if( val > MAX_DUTY )
                val = MAX_DUTY;
            timer_set_duty( val );
            duty = val;
        break;
        case PULSE:
        	timer_set_toff(val);
        break;
    }
}

int PulseGenerator::getCount() {
    return timer_get_count();
}

void PulseGenerator::start() {
    timer_start();
    started = true;
}

bool PulseGenerator::isStarted() {
    return started;
}

void PulseGenerator::stop() {
    timer_stop();
    started = false;
}

void PulseGenerator::setCount(uint32_t count) {
	timer_set_count(count);
}
