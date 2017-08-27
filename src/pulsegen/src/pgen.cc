#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

static struct hal_timer tim;

#define START_LEVEL 2000
#define MIN_LEVEL   724
#define MAX_LEVEL   3883

#define REAL_LEVEL( x ) ( x * 1.647 + 6 )
#define INTERN_LEVEL( x ) ( ( x - 6 * 1.0 ) / 1.647 )

PulseGenerator::PulseGenerator() {
    dac_init(START_LEVEL);
    timer_init(&tim);
    level = START_LEVEL;
}

void PulseGenerator::setMode(Mode mode) {

}

PulseGenerator::Mode PulseGenerator::getMode( void ) {

}

PulseGenerator::Mode PulseGenerator::toggleMode( void ) {

}

void PulseGenerator::setTon( int ton ) {

}

int PulseGenerator::getTon() {

}

int PulseGenerator::tonUp() {

}

int PulseGenerator::tonDown() {

}

void PulseGenerator::setLevel(int level) {
    int val = INTERN_LEVEL(level);
    if( val > MAX_LEVEL ) val = MAX_LEVEL;
    if( val < MIN_LEVEL ) val = MIN_LEVEL;
    this->level = val;
}

int PulseGenerator::getLevel() {
    return REAL_LEVEL(level);
}

int PulseGenerator::levelUp() {
    level++;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;
    dac_set(level);
    return REAL_LEVEL(level);
}

int PulseGenerator::levelDown() {
    level--;
    if( level <= MIN_LEVEL)
        level = MIN_LEVEL;
    dac_set(level);
    return REAL_LEVEL(level);
}
