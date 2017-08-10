#include <gfx/gfx.h>
#include <hal/SSD1351.h>
#include "ugui.h"

static UG_GUI gui;

static UG_RESULT _HW_FillFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
    UG_COLOR c );

static UG_RESULT _HW_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
        UG_COLOR c );

void gfx_init( void ) {
    UG_Init(&gui, disp_pset, 128, 128);
    UG_DriverRegister( DRIVER_FILL_FRAME, (void*) _HW_FillFrame );
    UG_DriverRegister( DRIVER_DRAW_LINE, (void*) _HW_DrawLine );
    UG_FillScreen(C_BLACK);
    UG_FontSelect( &FONT_8X12 ) ;
    UG_SetBackcolor( C_BLACK ) ;
    UG_SetForecolor( C_WHITE ) ;
    UG_PutString(0 ,10 , "ON : 0:000.00" );
    // UG_PutString(0 ,30 , "OFF: 00:000.00" );
    // UG_PutString(0 ,60 , "Count: 000" );
    // UG_PutString(0 ,80 , "Level: 0.00" );
    // UG_PutString(0 ,100 , "Pulse Mode" );
}

static UG_RESULT _HW_FillFrame ( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 ,
    UG_COLOR c ) {
    disp_fillframe(x1, y1, x2, y2, c);
    return UG_RESULT_OK;
}

static UG_RESULT _HW_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
        UG_COLOR c ){


    return UG_RESULT_FAIL;
}
