#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

static struct hal_timer tim;

PulseGenerator::PulseGenerator() {
    /* initialize the hardware */
    int start_lev = 2000;
    dac_init(start_lev);
    timer_init(&tim);
    level = start_lev;
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

int PulseGenerator::factorUp() {
    udFactor *= 10;
}

void PulseGenerator::setLevel(int level) {

}

int PulseGenerator::getLevel() {
    return level * lp + lo;
}

int PulseGenerator::levelUp() {
    level++;
    if (level > max_lev)
        level = max_lev;
    dac_set(level);
    return level * lp + lo;
}

int PulseGenerator::levelDown() {
    level--;
    if( level <= min_lev)
        level = min_lev;
    dac_set(level);
    return level * lp + lo;
}
