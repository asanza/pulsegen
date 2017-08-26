#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <hal/gpio.h>
#include <gfx/gfx.h>
#include <hal/timer.h>
#include <hal/dac.h>
#include <hal/keybd.h>

#define POWER_HOLD 17

static struct hal_timer tim;

/* handle interrupt request from keypress */
static void key_handler(enum key_type key);

static QueueHandle_t input_queue;
static Gfx ui;

void update_display(void* param) {
    enum key_type kinp;
    hal_gpio_init_out(6, 1);
    hal_gpio_init_out(5, 0);
    hal_gpio_init_out(POWER_HOLD, 1);
    while (1){
        if ( xQueueReceive(input_queue, &kinp, 250 / portTICK_PERIOD_MS) ) {
            switch(kinp) {
                case KEY_TA4:
                    /* change mode */
                    ui.toggleMode();
                break;
            }
        }
        hal_gpio_toggle(6);
        ui.update();
    }
}

static void input_task(void* param){
    while(1){
       // pulsegen.update(kinp);
    }
}

static void display_task(void *param){
    while(1){
    }
}

int main(void) {
    ui.init();
    dac_init(0x0300);
    timer_init(&tim);
    keybd_init(key_handler);
    input_queue = xQueueCreate(10, sizeof(enum key_type));
    xTaskCreate(update_display, "display", 1020, NULL, 3, NULL);
    vTaskStartScheduler();
}

void key_handler( enum key_type key) {
    portBASE_TYPE retval;
    xQueueSendFromISR(input_queue, &key, &retval);
    portEND_SWITCHING_ISR(retval);
}

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
