#ifndef TEXTFIELD_H_
#define  TEXTFIELD_H_

#include <stdint.h>

class UGui;

class TextField {
public:
    TextField(){inverted = false; _visible = true;}
    void setUp(int16_t x, int16_t y, const char* label, const char* fmt,
                const char* units);
    void setDisplay(UGui* Ui);
    void invert(bool value);
    void visible(bool value);
    void clear();
private:
    UGui* Ui;
    int16_t x,y;
    char label[10] = {0};
    char format[20] = {0};
    bool inverted, _visible;
    char units[10] = {0};
    char field[ 5 + sizeof (label) + sizeof (format) + sizeof (units) ] = {0};
    void update(void);
};


#endif
