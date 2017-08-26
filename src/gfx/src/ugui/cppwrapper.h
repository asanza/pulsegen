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
    void setForeground(uint32_t color);
    void putString(int16_t x, int16_t y, const char* string);
private:
};

#endif
