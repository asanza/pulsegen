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

extern "C" void user_init( void ) {
    UG_Init(&gui, disp_pset, 128, 128);
}

UGui::UGui() {
    UG_DriverRegister( DRIVER_FILL_FRAME, (void*) _HW_FillFrame );
    UG_DriverRegister( DRIVER_DRAW_LINE, (void*) _HW_DrawLine );
    UG_FontSelect( &FONT_8X12 ) ;
    UG_FontSetHSpace ( 0 );
    x = 0; y = 0;
}

void UGui::fillScreen(uint32_t color) {
    backcolor = color;
    UG_FillScreen(color);
}


void UGui::putString( int16_t x, int16_t y, const char* str ) {
    this->x = x; this->y = y;
    UG_PutString(this->x, this->y, (char*) str );
}

void UGui::putString( const char* str ) {
    UG_PutString(this->x, this->y, (char*) str);
}

void UGui::setTextColor(uint32_t color) {
    forecolor = color;
    UG_SetForecolor( color );
}

void UGui::setTextColor(uint32_t forecolor, uint32_t backcolor) {
    this->forecolor = forecolor;
    this->backcolor = backcolor;
    UG_SetForecolor( forecolor );
    UG_SetBackcolor( backcolor );
}

void UGui::setCursor(int16_t x, int16_t y) {
    this->x = x; this-> y = y;
}

void UGui::turnOn() {
    disp_on();
}

void UGui::turnOff() {
    disp_off();
}

void UGui::fillBlock( int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t color ) {
    UG_FillRoundFrame( x, y, x + w, y + h, 2, color );
}
