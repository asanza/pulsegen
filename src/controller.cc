#include "controller.h"

void Controller::init() {
    view.init();
    view.setLevel(model.getLevel());
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


void Controller::periodicTasks() {
    view.update();
}

void Controller::freq() {

}

void Controller::level() {

}

void Controller::duty() {

}

void Controller::mode() {

}

void Controller::count() {

}

void Controller::power() {

}

void Controller::decrease() {

}

void Controller::increase() {

}
