#ifndef TEXTFIELD_H_
#define  TEXTFIELD_H_

#include <stdint.h>

class UGui;

class TextField {
public:
    TextField(){inverted = false; _visible = true;_blink = false;}
    void setUp(int16_t x, int16_t y, const char* label, const char* fmt,
                const char* units);
    void setDisplay(UGui* Ui);
    void invert(bool value);
    void visible(bool value);
    int setBlink(int pos);
    void setValue(int value);
    void forceRedraw();
    void clear();
    void blink();
private:
    UGui* Ui;
    int16_t x,y, pos;
    char label[11] = {0};
    char format[15] = {0};
    bool inverted, _visible, _blink;
    char units[3] = {0};
    char field[ 1 + sizeof (label) + sizeof (format) + sizeof (units) ] = {0};
    int32_t value;
    void update(void);
    void printValue(void);
};


#endif
