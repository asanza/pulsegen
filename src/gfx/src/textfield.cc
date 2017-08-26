#include <gfx/textfield.h>
#include "ugui/cppwrapper.h"
#include <string.h>
#include "stdio.h"

void TextField::setUp(int16_t x, int16_t y, const char* label, const char* fmt,
            const char* units){
    this->x = x; this->y = y;
    this->clear();
    if(label) memcpy(this->label, label, sizeof(this->label));
    if(fmt) memcpy(this->format, fmt, sizeof(this->format));
    if(units) memcpy(this->units, units, sizeof(this->units));
    this->label[sizeof(this->label) - 1] = 0;
    this->format[sizeof(this->format) - 1] = 0;
    this->units[sizeof(this->units) - 1] = 0;
    update();
}

void TextField::setDisplay(UGui* ui) {
    this->Ui = ui;
}

void TextField::update(){
    if(!_visible) {
        return;
    }
    //if(inverted)
        Ui->setTextColor(0xFFFF, 0x0000);
    //else
    //    Ui->setTextColor(0xFFFF, 0x0000);
    sprintf(field, "%s %s %s", label, format, units);
    Ui->setCursor(x,y);
    Ui->putString(&field[0]);
}

void TextField::invert(bool value) {
    this->inverted = value;
    //update();
}

void TextField::visible(bool value) {
    this->_visible = value;
    clear();
    update();
}

void TextField::clear(){
    int16_t _x,_y;
    uint16_t w,h;
    //Ui->getTextBounds(field,x,y,&_x,&_y, &w, &h);
    //Ui->fillRect(x,y,w,h,0x0000);
}
