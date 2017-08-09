#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <hal/SSD1351.h>

void blink(void* param) {
    hal_gpio_init_out(6, 1);
    disp_init();
    while (1){
        vTaskDelay(1000/portTICK_RATE_MS);
        hal_gpio_toggle(6);
    }
}

int main(void) {
    xTaskCreate(blink, "blink", 100, NULL, 3, NULL);
    vTaskStartScheduler();
}
