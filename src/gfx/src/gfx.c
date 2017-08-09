#include <gfx/gfx.h>
#include <hal/SSD1351.h>
#include "ugui.h"

static UG_GUI gui;

static UG_RESULT _HW_FillFrame ( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 ,
    UG_COLOR c );

void gfx_init( void ) {
    UG_Init(&gui, disp_pset, 128, 128);
    UG_DriverRegister( DRIVER_FILL_FRAME, (void*) _HW_FillFrame );
    UG_FillScreen(C_BLACK);
    UG_FontSelect( &FONT_6X10 ) ;
    UG_SetBackcolor( C_BLACK ) ;
    UG_SetForecolor( C_CYAN ) ;
    UG_PutString( 0 , 0 , "Hello World!" );
}

static UG_RESULT _HW_FillFrame ( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 ,
    UG_COLOR c ) {
    disp_fillframe(x1, y1, x2, y2, c);
    return UG_RESULT_OK;
}
