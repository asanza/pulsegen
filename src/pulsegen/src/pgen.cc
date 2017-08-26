#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

static struct hal_timer tim;

PulseGenerator::PulseGenerator() {
    /* initialize the hardware */
    dac_init(0x0300);
    timer_init(&tim);
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
