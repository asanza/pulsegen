#ifndef SYSTATE_H
#define SYSTATE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

    enum mode
    {
        PULSE,
        PWM
    };

    enum error
    {
        ERROR_NONE,
        ERROR_UNSUPORTED_MODE
    };

    enum system_setting
    {
        PULSE_TIME,
        PAUSE_TIME,
        LEVEL,
        COUNT,
        FREQUENCY,
        DUTY,
        NONE
    };

    enum system_event
    {
        EVT_NONE,
        EVT_KEY_MODE,
        EVT_KEY_FREQ,
        EVT_KEY_DUTY,
        EVT_KEY_LEVEL,
        EVT_KEY_COUNT,
        EVT_ENC_DOWN,
        EVT_ENC_UP,
        EVT_ENC_PUSH
    };

    struct system_state
    {
        bool (*get_active)(void);
        bool (*get_output)(void);
        enum error (*get_error)(void);
        void (*set_error)(enum error error);
        enum mode (*get_mode)(void);
        /* pulse */
        uint32_t (*get_pulse_time)(void);
        uint32_t (*get_pause_time)(void);
        uint32_t (*get_frequency)(void);
        uint32_t (*get_duty)(void);
        uint32_t (*get_level)(void);
        uint32_t (*get_count)(void);
        /**
         * @brief Return which setting is being adjusted. 
         * The position return value is which position in the 
         * setting is being adjusted. 1 = first digit, 10 = second
         * digit, 100 = third digit, etc.
         */
        enum system_setting (*get_adjust_setting)(uint32_t *position);
        void (*update)(enum system_event evt, void *args);
        void (*set_parameter)(enum system_setting param, uint32_t value);
    };

#ifdef __cplusplus
}
#endif

#endif /* SYSTATE_H */
