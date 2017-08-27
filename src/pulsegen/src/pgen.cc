#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

#define START_LEVEL 330
#define MIN_LEVEL   150
#define MAX_LEVEL   620
#define START_FREQ  1000
#define MAX_FREQ    350000
#define MIN_FREQ    10

#define INTERN_LEVEL( x ) ( ( x - 0.5719 * 1.0 ) / 0.1647 )

PulseGenerator::PulseGenerator() {
    dac_init(INTERN_LEVEL(START_LEVEL));
    timer_init( HAL_TIMER_PWM );
    timer_set_freq( START_FREQ );
    started = false;
    level = START_LEVEL;
    freq = START_FREQ;
    mode = PWM;
}

void PulseGenerator::setMode(Mode mode) {
    this->mode = mode;
}

PulseGenerator::Mode PulseGenerator::getMode( void ) {
    return mode;
}

PulseGenerator::Mode PulseGenerator::toggleMode( void ) {
    if(mode == PULSE)
        mode = PWM;
    else
        mode = PULSE;
    return mode;
}

void PulseGenerator::setTonFreq( int value ) {
   switch(mode) {
       case PWM:
            if( value > MAX_FREQ )
                value = MAX_FREQ;
            if( value < MIN_FREQ )
                value = MIN_FREQ;
            timer_set_freq( value );
            freq = value;
            break;
   }
}

int PulseGenerator::getTonFreq() {
    switch(mode) {
        case PWM: return freq;
        case PULSE: return ton;
    }
    return 0;
}

int PulseGenerator::tonFreqUp() {
    return 0;
}

int PulseGenerator::tonFreqDown() {
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

int PulseGenerator::levelUp() {
    level++;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;
    dac_set(INTERN_LEVEL(level));
    return level;
}

int PulseGenerator::levelDown() {
    level--;
    if( level <= MIN_LEVEL)
        level = MIN_LEVEL;
    dac_set(INTERN_LEVEL(level));
    return level;
}

int PulseGenerator::getToffDuty() {
    switch(mode) {
        case PWM: return duty;
        case PULSE: return toff;
    }
    return 0;
}

int PulseGenerator::getCount() {
    return 0;
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
