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
            view.setFreq(model.getFreq());
            view.setDuty(model.getDuty());
        break;
        case PulseGenerator::Mode::PULSE:
            view.setPulseMode();
            view.setTon(model.getTon());
            view.setToff(model.getToff());
            view.setCount(model.getCount());
        break;
    }
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
}

void Controller::level() {
    if( adj != LEVEL ) {
        clearBlinks();
        adj = LEVEL;
    }

    blinkpos = view.blinkLevel(++blinkpos);
}

void Controller::toff() {
    if( adj != TOFF ) {
        clearBlinks();
        adj = TOFF;
    }
    blinkpos = view.blinkDuty(++blinkpos);
}

void Controller::mode() {
    clearBlinks();
    model.toggleMode();
    updateMode();
}

void Controller::count() {
    if( adj != COUNT ) {
        clearBlinks();
        adj = COUNT;
    }

    blinkpos = view.blinkCount(++blinkpos);
}

void Controller::power() {

}

void Controller::decrease() {

}

void Controller::increase() {

}
