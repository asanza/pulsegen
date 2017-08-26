#include <pulsegen/pgen.h>
#include <hal/timer.h>
#include <hal/dac.h>

static struct hal_timer tim;

PulseGenerator::PulseGenerator() {
    /* initialize the hardware */
    dac_init(0x0300);
    timer_init(&tim);
}
