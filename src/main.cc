#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <hal/gpio.h>
#include <hal/keybd.h>

#include "controller.h"

#define POWER_HOLD 17

/* handle interrupt request from keypress */
static void key_handler(enum key_type key);

static QueueHandle_t input_queue;

static Controller dev;

static void process_key(enum key_type kinp) {
    switch(kinp) {
        /* ontime/freq */
        case KEY_TA1: dev.ton(); break;
        /* level */
        case KEY_TA2: dev.level(); break;
        /* offtime duty */
        case KEY_TA3: dev.toff(); break;
        /* change mode */
        case KEY_TA4: dev.mode(); break;
        /* count */
        case KEY_TA5: dev.count(); break;
        /* power/trigger */
        case KEY_POW: dev.power(); break;
        /* encoder increment */
        case ENC_INC: dev.increase(); break;
        /* encoder decrement */
        case ENC_DEC: dev.decrease(); break;
    }
}

void update_display(void* param) {
    enum key_type kinp;
    hal_gpio_init_out(6, 1);
    hal_gpio_init_out(5, 0);
    hal_gpio_init_out(POWER_HOLD, 1);
    while (1){
        if ( xQueueReceive(input_queue, &kinp, 250 / portTICK_PERIOD_MS) ) {
            do {
                process_key(kinp);
            } while ( xQueueReceive(input_queue, &kinp, 0));
        }
        hal_gpio_toggle(6);
        dev.periodicTasks();
    }
}

int main(void) {
    dev.init();
    keybd_init(key_handler);
    input_queue = xQueueCreate(10, sizeof(enum key_type));
    xTaskCreate(update_display, "display", 1020, NULL, 3, NULL);
    vTaskStartScheduler();
}

/* handle key press events */
void key_handler( enum key_type key) {
    portBASE_TYPE retval;
    xQueueSendFromISR(input_queue, &key, &retval);
    portEND_SWITCHING_ISR(retval);
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
