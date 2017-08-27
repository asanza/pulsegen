#include <gfx/textfield.h>
#include "ugui/cppwrapper.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"

void TextField::setUp(int16_t x, int16_t y, const char* label, const char* fmt,
            const char* units){
    this->x = x; this->y = y;
    if(label) memcpy(this->label, label, sizeof(this->label));
    if(fmt) memcpy(this->format, fmt, sizeof(this->format));
    if(units) memcpy(this->units, units, sizeof(this->units));
    this->label[sizeof(this->label) - 1] = 0;
    this->format[sizeof(this->format) - 1] = 0;
    this->units[sizeof(this->units) - 1] = 0;
    this->clear();
    Ui->setTextColor(COLOR_WHITE, COLOR_BLACK);
    forceRedraw();
}

void TextField::setDisplay(UGui* ui) {
    this->Ui = ui;
}

void TextField::update(){
    if(!_visible) {
        return;
    }
    /* only do update if the string has changed */
    if( strstr(field, label) && strstr(field, format) && strstr(field, units) ){
        return;
    }
    sprintf(field, "%s %s %s", label, format, units);
    Ui->setCursor(x,y);
    Ui->putString(field);
}

void TextField::forceRedraw() {
    if(!_visible) {
        clear();
        return;
    }
    sprintf(field, "%s %s %s", label, format, units);
    Ui->setCursor(x,y);
    Ui->putString(field);
}

void TextField::invert(bool value) {
    this->inverted = value;
}

void TextField::visible(bool value) {
    if( _visible == value) return;
    this->_visible = value;
    if(!_visible)
        clear();
    forceRedraw();
}

void TextField::clear(){
    Ui->setTextColor(COLOR_BLACK);
    Ui->setCursor(x,y);
    Ui->putString(field);
    Ui->setTextColor(COLOR_WHITE);
}

void TextField::blink() {
    printValue();
    update();
}

int TextField::setBlink( int pos ) {
    int i, count = 0;
    if( pos < 0) return 0;
    i = strlen(format);
    while (i--) {
        if(format[i] == ':' || format[i] == '.') {
            continue;
        } else if ( format [i] == 0 ) {
            /* end of string */
            return 0;
        }
        count ++;
    }
    if( pos > count) pos = 0;
    this->pos = pos;
    return pos;
}

void TextField::setValue( int val ) {
    this->value = val;
}

void TextField::printValue( void ) {
    /* how to print the field value into format:
       well, we take the digits from low to hi and
       put them in the respective position */
    int p = pos;
    char res[3];
    int i = strlen(format);
    int temp = value;
    while( i-- ) {
        if(format[i] == ':' || format[i] == '.') {
            continue;
        } else if ( format [i] == 0 ) {
            /* end of string */
            return;
        }
        p--;
        utoa(temp % 10, res, 10);
        temp = temp / 10;
        if(p < 0 || p > 0) {
            format[i] = res[0];
            continue;
        }
        if(_blink) {
            format[i] = res[0];
        } else {
            format[i] = '_';
        }
        _blink = !_blink;
    }
}
