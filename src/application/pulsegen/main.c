#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <ssd1351.h>

#define GREEN_LED  GPIO_PIN(GPIO_PORT_A, 6)
#define RED_LED  GPIO_PIN(GPIO_PORT_A, 5)

#define POWER_HOLD GPIO_PIN(GPIO_PORT_B, 1)

void test(void* arg)
{
    hal_gpio_init_out(POWER_HOLD, 1);
    hal_gpio_init_out(RED_LED, 0);
    hal_gpio_init_out(GREEN_LED, 1);
    while(1) {
        hal_gpio_toggle(RED_LED);
        hal_gpio_toggle(GREEN_LED);
        vTaskDelay(pdMS_TO_TICKS(125));
    }
}

void display( void * arg ) 
{
    uint32_t i = 0;
    disp_init();
    disp_on();
    disp_checkerboard();
    while(1) {
        // disp_fillframe(0, 0, 100, 100, i++);
    }
}

int main(void)
{
    xTaskCreate(test, "test", 124, NULL, 3, NULL);
    xTaskCreate(display, "disp", 124, NULL, 3, NULL);
    vTaskStartScheduler();
    while(1);
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ) {
    asm ("BKPT");
    while(1) ;
}

void vApplicationIdleHook( void ) {

}

void vApplicationMallocFailedHook( void ) {
    asm ("BKPT");
    while(1) ;
}
