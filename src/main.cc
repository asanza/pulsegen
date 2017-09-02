#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <hal/keybd.h>
#include <sys/evt.h>

#define POWER_HOLD 17

/* handle interrupt request from keypress */
// static void key_handler(enum key_type key);

// static void process_key(Controller& dev, enum key_type kinp) {
//     switch(kinp) {
//         /* ontime/freq */
//         case KEY_TA1: dev.ton(); break;
//         /* level */
//         case KEY_TA2: dev.level(); break;
//         /* offtime duty */
//         case KEY_TA3: dev.toff(); break;
//         /* change mode */
//         case KEY_TA4: dev.mode(); break;
//         /* count */
//         case KEY_TA5: dev.count(); break;
//         /* power/trigger */
//         case KEY_POW: dev.power(); break;
//         /* encoder increment */
//         case ENC_INC: dev.increase(); break;
//         /* encoder decrement */
//         case ENC_DEC: dev.decrease(); break;
//     }
// }

void display_listener( enum EventType type, uint32_t data ) {
    // switch(type){
    //     case TON_CHANGED:
    //     case TOFF_CHANGED:
    //     case FREQUENCY_CHANGED:
    //     case DUTY_CHANGED:
    //     case LEVEL_CHANGED:
    //     case COUNT_CHANGED:
    //     case MODE_CHANGED:
    // }
}

void device_listener( enum EventType type, uint32_t data ) {
    // switch(type) {
    //     case KEY_POWER:
    //     case KEY_MODE:
    //     case KEY_FREQ:
    //     case KEY_DUTY:
    //     case KEY_LEVEL:
    //     case KEY_COUNT:
    //     case ENCODER_DECREASE:
    //     case ENCODER_INCREASE:
    // }
}

void event_loop(void* param) {
    while (1){
        evt_loop();
        //display.loop();
        //device.loop();
    }
}

/* handle key press events */
void key_handler( enum key_type key) {
    EventType type;
    switch(key) {
        /* ontime/freq */
        case KEY_TA1: type = KEY_FREQ ; break;
        /* level */
        case KEY_TA2: type = KEY_LEVEL; break;
        /* offtime duty */
        case KEY_TA3: type = KEY_DUTY; break;
        /* change mode */
        case KEY_TA4: type = KEY_MODE; break;
        /* count */
        case KEY_TA5: type = KEY_COUNT; break;
        /* power/trigger */
        case KEY_POW: type = KEY_POWER; break;
        /* encoder increment */
        case ENC_INC: type = ENCODER_DECREASE; break;
        /* encoder decrement */
        case ENC_DEC: type = ENCODER_INCREASE; break;
    }
    evt_queue_from_isr(type, 0);
}

int main(void) {
    hal_gpio_init_out(5, 0);
    hal_gpio_init_out(6, 1);
    hal_gpio_init_out(POWER_HOLD, 1);
    keybd_init(key_handler);
    evt_init();
    evt_register_listener(display_listener);
    evt_register_listener(device_listener);
    xTaskCreate(event_loop, "display", 1020, NULL, 3, NULL);
    vTaskStartScheduler();
    return 1;
}

/* os hook functions */
extern "C" {

    void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ) {
        asm("BKPT");
        while(1);
    }

    void vApplicationIdleHook( void ) {

    }

    void vApplicationMallocFailedHook( void ) {
        asm("BKPT");
        while(1);
    }

}
