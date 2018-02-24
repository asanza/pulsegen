
#ifndef H_CTRL_
#define H_CTRL_

#include <stdint.h>

class PulseGenerator {
public:

    PulseGenerator();

    enum Mode{PWM, PULSE};
    /**
     * Set pulse generator mode. 
     * @param mode [description]
     */
    void setMode(Mode mode);
    Mode toggleMode(void);
    Mode getMode( void );

    void setCount( uint32_t count );
    int getCount( void );

    void setTonFreq( int freq );
    int getTonFreq( void );

    void setToffDuty( int duty );
    int getToffDuty( void );

    void setLevel(int level);
    int getLevel( void );

    void start( void );
    void stop( void );

    bool isStarted( void );

private:
    Mode mode;
    uint32_t duty, count, ton, toff, level;
    bool started;
};

#endif /* H_CTRL_ */
