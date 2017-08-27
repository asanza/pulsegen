#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <pulsegen/pgen.h>
#include <gfx/gfx.h>

class Controller {
public:
    void init();
    void increase();
    void mode();
    void decrease();
    void power();
    void count();
    void duty();
    void level();
    void freq();
    void periodicTasks();
private:
    Gfx view;
    PulseGenerator model;
};

#endif
