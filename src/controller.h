#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <pulsegen/pgen.h>
#include <gfx/gfx.h>

class Controller {
public:
    Controller();
    void increase();
    void mode();
    void decrease();
    void power();
    void count();
    void toff();
    void level();
    void ton();
    void notify();
    void periodicTasks();
private:
    void updateMode();
    void clearBlinks();
    Gfx view;
    PulseGenerator model;
    int blinkpos = 0;
    enum Adj{ TON, TOFF, COUNT, LEVEL, NONE };
    enum Adj adj = NONE;
};

#endif
