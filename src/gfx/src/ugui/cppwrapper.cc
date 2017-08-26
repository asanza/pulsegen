#include "cppwrapper.h"
#include <hal/SSD1351.h>
#include "ugui.h"

static UG_GUI gui;

static UG_RESULT _HW_FillFrame ( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 ,
    UG_COLOR c ) {
    disp_fillframe(x1, y1, x2, y2, c);
    return UG_RESULT_OK;
}

static UG_RESULT _HW_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
        UG_COLOR c ){

    return UG_RESULT_FAIL;
}


UGui::UGui() {
    disp_init();
    UG_Init(&gui, disp_pset, 128, 128);
    UG_DriverRegister( DRIVER_FILL_FRAME, (void*) _HW_FillFrame );
    UG_DriverRegister( DRIVER_DRAW_LINE, (void*) _HW_DrawLine );
    UG_FontSelect( &FONT_8X12 ) ;
}

void UGui::fillScreen(uint32_t color) {
    UG_FillScreen(color);
}


void UGui::putString( int16_t x, int16_t y, const char* str ) {
    UG_PutString(x, y, (char*) str );
}

void UGui::setForeground(uint32_t color) {
    UG_SetForecolor( color );
}

void UGui::setBackground(uint32_t color) {
    UG_SetBackcolor( color );
}
