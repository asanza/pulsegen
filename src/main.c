#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>

void blink(void* param) {
    hal_gpio_init_out(6, 1);
    while (1){
        vTaskDelay(500/portTICK_RATE_MS);
        hal_gpio_toggle(6);
    }
}

int main(void) {
    xTaskCreate(blink, "blink", 100, NULL, 3, NULL);
    vTaskStartScheduler();
}



void _init(void) {

}
