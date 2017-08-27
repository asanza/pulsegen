#include <gfx/gfx.h>
#include "ugui/cppwrapper.h"

static UGui ui;

#define BACKGROUND_COLOR COLOR_BLACK

Gfx::Gfx( void ) {
}

void Gfx::clear( void ) {
}

void Gfx::init( void ) {
    int i;
    ui.turnOn();
    for( i = 0; i < widget_count; i++ ) {
        widgets[i].setDisplay(&ui);
    }
    setPulseMode();
}

void Gfx::update( void ) {
    int i;
    for(i = 0; i < widget_count; i++){
         widgets[i].blink();
    }
}

void Gfx::setLevel( int value ) {
    widgets[3].setValue( value );
}

void Gfx::setPulseMode() {
    widgets[0].setUp(5, 10, "Low:", "00:000.00", "");
    widgets[1].setUp(5, 30, "Hi :", "00:000.00", "");
    widgets[2].visible(true);
    widgets[2].setUp(5, 60, "Count:", "0000", "");
    widgets[3].setUp(5, 80, "Level:", "0.000", "");
    widgets[4].setUp(25, 110, "Pulse Mode", "", "");
}

void Gfx::setPWMMode() {
    widgets[0].setUp(5, 10, "Frq:", "000000", "Hz");
    widgets[1].setUp(5, 30, "Dty:", "000", "%");
    widgets[2].visible(false);
    widgets[3].setUp(5, 80, "Level:", "0.000", "");
    widgets[4].setUp(25, 110, "PWM Mode", "", "");
}

void Gfx::toggleMode() {
    if(pulseMode)
        setPWMMode();
    else
        setPulseMode();
    pulseMode = !pulseMode;
}
