#ifndef SYS_EVT_H_
#define SYS_EVT_H_

#ifdef __cplusplus
extern "C" {
#endif

enum EventType {
    KEY_POWER,
    KEY_MODE,
    KEY_FREQ,
    KEY_DUTY,
    KEY_LEVEL,
    KEY_COUNT,
    ENCODER_INCREASE,
    ENCODER_DECREASE,
    FREQUENCY_CHANGED,
    TON_CHANGED,
    TOFF_CHANGED,
    DUTY_CHANGED,
    LEVEL_CHANGED,
    COUNT_CHANGED,
    MODE_CHANGED,
};

typedef void(*event_listener_t)(enum EventType type, uint32_t data);

void evt_register_listener(event_listener_t listener);
void evt_queue_from_isr(enum EventType type, uint32_t data);
void evt_queue(enum EventType type, uint32_t data);

#ifdef __cplusplus
}
#endif

#endif
