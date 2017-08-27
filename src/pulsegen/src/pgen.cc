#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

static struct hal_timer tim;

#define START_LEVEL 330
#define MIN_LEVEL   150
#define MAX_LEVEL   620

#define INTERN_LEVEL( x ) ( ( x - 0.5719 * 1.0 ) / 0.1647 )

PulseGenerator::PulseGenerator() {
    dac_init(INTERN_LEVEL(START_LEVEL));
    timer_init(&tim);
    level = START_LEVEL;
    mode = PULSE;
}

void PulseGenerator::setMode(Mode mode) {

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

void PulseGenerator::setTonFreq( int ton ) {

}

int PulseGenerator::getTonFreq() {
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
    return 0;
}

int PulseGenerator::getCount() {
    return 0;
}
