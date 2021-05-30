#ifndef UGUI_CPPWRAPPER_
#define UGUI_CPPWRAPPER_

#include <stdint.h>

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000

class UGuiFont;

class UGui {
public:
    UGui();
    void fillScreen(uint32_t color);
    void fontSelect(UGuiFont* font);
    void setBackground(uint32_t color);
    void setTextColor(uint32_t color);
    void setTextColor(uint32_t forecolor, uint32_t backcolor);
    void putString(int16_t x, int16_t y, const char* string);
    void putString( const char* str );
    void setCursor(int16_t x, int16_t y);
    void turnOff();
    void turnOn();
    void fillBlock( int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t color);
private:
    int16_t x, y;
    uint32_t forecolor, backcolor;
};

#endif
