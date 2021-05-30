#include <gfx/gfx.h>
#include "ugui/cppwrapper.h"

static UGui ui;

#define BACKGROUND_COLOR COLOR_BLACK

Gfx::Gfx( void ) {
    int i;
    ui.turnOn();
    for( i = 0; i < widget_count; i++ ) {
        widgets[i].setDisplay(&ui);
    }
    setPulseMode();
}

void Gfx::clear( void ) {
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
    widgets[3].setUp(5, 80, "Level:", "0.00", "");
    widgets[4].setUp(25, 110, "Pulse Mode", "", "");
}

void Gfx::setPWMMode() {
    widgets[0].setUp(5, 10, "Frq:", "000000", "Hz");
    widgets[1].setUp(5, 30, "Dty:", "000", "%");
    widgets[2].visible(false);
    widgets[3].setUp(5, 80, "Level:", "0.00", "");
    widgets[4].setUp(25, 110, "PWM Mode", "", "");
}

void Gfx::toggleMode() {
    if(pulseMode)
        setPWMMode();
    else
        setPulseMode();
    pulseMode = !pulseMode;
}

void Gfx::setTonFreq(int val) {
    widgets[0].setValue(val);
}

void Gfx::setToffDuty(int val) {
    widgets[1].setValue(val);
}

void Gfx::setCount(int val) {
    widgets[2].setValue(val);
}

int Gfx::blinkLevel( int val ) {
    return widgets[3].setBlink(val);
}

int Gfx::blinkFreq(int val) {
    return widgets[0].setBlink(val);
}

int Gfx::blinkDuty(int val) {
    return widgets[1].setBlink(val);
}

int Gfx::blinkTon(int val) {
    return widgets[0].setBlink(val);
}

int Gfx::blinkToff(int val) {
    return widgets[1].setBlink(val);
}

int Gfx::blinkCount(int val) {
    return widgets[2].setBlink(val);
}

void Gfx::outputActive( bool val ) {
    if ( val ) {
        ui.fillBlock(5, 110, 10, 10, 0xFF0000);
    } else {
        ui.fillBlock(5, 110, 10, 10, 0x000000);
    }
}
