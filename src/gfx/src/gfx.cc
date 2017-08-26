#include <gfx/gfx.h>
#include "ugui/cppwrapper.h"

static UGui ui;

#define BACKGROUND_COLOR COLOR_BLACK

Gfx::Gfx( void ) {
}


void Gfx::Clear( void ) {
    //ui.fillScreen(COLOR_BLACK);
    TonFreq.setDisplay(&ui);
    TonFreq.setUp(0, 0, "HELLO", "HEllo", "lo");
}
