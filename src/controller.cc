#include "controller.h"

static const int pow10[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
};

void Controller::init() {
    view.init();
    updateMode();
    view.outputActive(model.isStarted());
    view.setLevel(model.getLevel());
    view.setFreq(model.getTonFreq());
    view.setDuty(model.getToffDuty());
    view.setCount(model.getCount());
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
    if ( model.isStarted() ) {
        model.stop();
    }
    else {
        model.start();
    }
    view.outputActive(model.isStarted());
}

void Controller::decrease() {
    switch( adj ) {
        case TON:
            model.setTonFreq(model.getTonFreq() - pow10[blinkpos - 1]);
            view.setTon(model.getTonFreq());
        break;
        case LEVEL :
            model.setLevel(model.getLevel() - pow10[blinkpos - 1]);
            view.setLevel( model.getLevel());
        break;
    }
}

void Controller::increase() {
    switch( adj ) {
        case TON:
            model.setTonFreq(model.getTonFreq() + pow10[blinkpos - 1]);
            view.setTon(model.getTonFreq());
        break;
        case LEVEL :
            model.setLevel(model.getLevel() + pow10[blinkpos - 1]);
            view.setLevel( model.getLevel());
        break;
    }
}
