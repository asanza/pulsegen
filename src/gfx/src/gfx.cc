#include <gfx/gfx.h>
#include "ugui/cppwrapper.h"

static UGui ui;

Gfx::Gfx( void ) {
    // UG_FillScreen(C_WHITE);
    // UG_SetBackcolor( C_WHITE ) ;
}


void Gfx::Clear( void ) {
    //ui.fillScreen(COLOR_WHITE);
    //ui.setForeground(COLOR_BLACK);
    //ui.setBackground(COLOR_WHITE);
    ui.putString(5, 10, "ON : 00:000.0");
    // UG_SetForecolor( C_BLACK ) ;
    // UG_PutString(0 ,10 , (char*)"ON : 00:000.00" );
    // UG_PutString(0 ,30 , (char*)"OFF: 00:000.00" );
    // UG_PutString(0 ,60 , (char*)"Count: 000" );
    // UG_PutString(0 ,80 , (char*)"Level: 0.00" );
    // UG_PutString(0 ,100 , (char*)"Pulse Mode" );
}
