#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <gfx/gfx.h>
#include <hal/timer.h>
#include <hal/dac.h>
#include <hal/keybd.h>

#define POWER_HOLD 17

void blink(void* param) {
    hal_gpio_init_out(6, 1);
    hal_gpio_init_out(5, 0);
    hal_gpio_init_out(POWER_HOLD, 1);
    gfx_init();
    while (1){
        vTaskDelay(250/portTICK_RATE_MS);
        hal_gpio_toggle(6);
    }
}

struct hal_timer tim;

void key_handler( enum key_type key) {
    switch(key) {
        case KEY_POW: ; break;
        case KEY_TA1: ; break;
        case KEY_TA2: ; break;
    }
}

int main(void) {
    dac_init(0x0300);
    timer_init(&tim);
    keybd_init(key_handler);
    xTaskCreate(blink, "blink", 100, NULL, 3, NULL);
    vTaskStartScheduler();
}
