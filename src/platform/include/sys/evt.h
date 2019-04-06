#ifndef SYS_EVT_H_
#define SYS_EVT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

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

    typedef void (*event_listener_t)(enum system_event type, uint32_t data);
    void evt_init(void);
    void evt_register_listener(event_listener_t listener);
    void evt_queue_from_isr(enum system_event type, uint32_t data);
    void evt_queue(enum system_event type, uint32_t data);
    void evt_loop(void);

#ifdef __cplusplus
}
#endif

#endif
