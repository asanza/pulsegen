
#ifndef H_CTRL_
#define H_CTRL_

#include <stdint.h>

class PulseGenerator {
public:

    PulseGenerator();

    enum Mode{PWM, PULSE};
    void setMode(Mode mode);
    Mode toggleMode(void);
    Mode getMode( void );

    /* pulse mode interface */
    void setTon(int ton);
    int getTon( void );
    int tonUp( void );
    int tonDown( void );

    void setToff( int toff );
    int getToff( void );
    int toffUp( void );
    int toffDown( void );

    void setCount( int count );
    int getCount( void );
    int countUp( void );
    int countDown( void );

    /* pwm mode interface */
    void setFreq( int freq );
    int getFreq( void );
    int freqUp( void );
    int freqDown( void );

    void setDuty( int duty );
    int getDuty( void );
    int setUp( void );
    int setDown( void );

    /* common interface */
    void setLevel(int level);
    int getLevel( void );
    int levelUp( void );
    int levelDown( void );
    void start( void );
    void stop( void );

private:
    Mode mode;
    int freq, duty, count, ton, toff, level;
    const int lo = 6;
    const float lp = 1.647;
};

#endif /* H_CTRL_ */
