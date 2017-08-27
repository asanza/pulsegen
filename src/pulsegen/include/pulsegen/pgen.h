
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

    void setCount( int count );
    int getCount( void );
    int countUp( void );
    int countDown( void );

    void setTonFreq( int freq );
    int getTonFreq( void );
    int tonFreqUp( void );
    int tonFreqDown( void );

    void setToffDuty( int duty );
    int getToffDuty( void );
    int toffDutyUp( void );
    int toffDutyDown( void );

    void setLevel(int level);
    int getLevel( void );
    int levelUp( void );
    int levelDown( void );
    void start( void );
    void stop( void );

    bool isStarted( void );

private:
    Mode mode;
    int freq, duty, count, ton, toff, level;
    bool started;
};

#endif /* H_CTRL_ */
