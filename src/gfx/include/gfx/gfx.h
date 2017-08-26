
#ifndef H_GFX_
#define H_GFX_

#include "textfield.h"

class Gfx {
public:
    Gfx( void );
    void clear( void );
    void update( void );
    void init( void );
    void toggleMode();
private:
    static const int widget_count = 5;
    TextField widgets[widget_count];
    void setPulseMode( void );
    void setPWMMode( void );
    bool pulseMode = true;
};

#endif /* H_GFX_ */
