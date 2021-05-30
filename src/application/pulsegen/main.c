#include <FreeRTOS.h>
#include <task.h>

void test(void* arg)
{
    while(1);
}

void main(void)
{
    xTaskCreate(test, "test", 124, NULL, 3, NULL);
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
