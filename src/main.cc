#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <hal/gpio.h>
#include <gfx/gfx.h>
#include <hal/keybd.h>
#include <pulsegen/pgen.h>

#define POWER_HOLD 17

/* handle interrupt request from keypress */
static void key_handler(enum key_type key);

static QueueHandle_t input_queue;
static Gfx ui;
static PulseGenerator device;

void update_display(void* param) {
    enum key_type kinp;
    hal_gpio_init_out(6, 1);
    hal_gpio_init_out(5, 0);
    hal_gpio_init_out(POWER_HOLD, 1);
    int i = 100;
    while (1){
        if ( xQueueReceive(input_queue, &kinp, 250 / portTICK_PERIOD_MS) ) {
            switch(kinp) {
                case KEY_TA4:
                    /* change mode */
                    ui.toggleMode();
                break;
                case ENC_INC:
                    ui.setValue( ++i );
                break;
                case ENC_DEC:
                    ui.setValue( --i );
                break;
            }
        }
        hal_gpio_toggle(6);
        ui.update();
    }
}

int main(void) {
    ui.init();
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
