
#ifndef H_GFX_
#define H_GFX_

#include "textfield.h"

class Gfx {
public:
    Gfx( void );
    void clear( void );
    void update( void );
    void toggleMode();

    void setPulseMode( void );
    void setPWMMode( void );
    void setLevel( int val );
    void setTonFreq(int val);
    void setToffDuty(int val);
    void setCount(int val);

    int blinkLevel( int val );
    int blinkFreq(int val);
    int blinkDuty(int val);
    int blinkTon(int val);
    int blinkToff(int val);
    int blinkCount(int val);

    void outputActive( bool value );

private:
    static const int widget_count = 5;
    TextField widgets[widget_count];
    bool pulseMode = true;
};

#endif /* H_GFX_ */
