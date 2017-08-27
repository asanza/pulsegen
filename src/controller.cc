#include "controller.h"

void Controller::init() {
    view.init();
    view.setLevel(model.getLevel());
    updateMode();
}

void Controller::updateMode() {
    switch(model.getMode()) {
        case PulseGenerator::Mode::PWM:
            view.setPWMMode();
        break;
        case PulseGenerator::Mode::PULSE:
            view.setPulseMode();
            view.setCount(model.getCount());
        break;
    }
    view.setTon(model.getTonFreq());
    view.setToff(model.getToffDuty());
}

void Controller::clearBlinks() {
    view.blinkLevel(0);
    view.blinkTon(0);
    view.blinkToff(0);
    view.blinkCount(0);
    blinkpos = 0;
}

void Controller::periodicTasks() {
    view.update();
}

void Controller::ton() {
    if( adj != TON ){
        clearBlinks();
        adj = TON;
    }
    blinkpos = view.blinkTon(++blinkpos);
    if( blinkpos == 0 ) adj = NONE;
}

void Controller::level() {
    if( adj != LEVEL ) {
        clearBlinks();
        adj = LEVEL;
    }

    blinkpos = view.blinkLevel(++blinkpos);
    if( blinkpos == 0 ) adj = NONE;
}

void Controller::toff() {
    if( adj != TOFF ) {
        clearBlinks();
        adj = TOFF;
    }
    blinkpos = view.blinkDuty(++blinkpos);
    if( blinkpos == 0 ) adj = NONE;
}

void Controller::mode() {
    clearBlinks();
    model.toggleMode();
    updateMode();
    adj = NONE;
}

void Controller::count() {
    if( adj != COUNT ) {
        clearBlinks();
        adj = COUNT;
    }

    blinkpos = view.blinkCount(++blinkpos);
    if( blinkpos == 0 ) adj = NONE;
}

void Controller::power() {
    adj = NONE;
    clearBlinks();
}

void Controller::decrease() {
    switch( adj ) {
        case TON:
            view.setTon(model.tonFreqDown());
        break;
    }
}

void Controller::increase() {

}
