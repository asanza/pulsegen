/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Friday January 25th 2019
 * Author: diego
 */

#include <FreeRTOS.h>
#include <task.h>

void os_start( void )
{
  vTaskStartScheduler();
}

void os_enter_critical( void ) {
	portENTER_CRITICAL();
}

void os_exit_critical( void ) {
	portEXIT_CRITICAL();
}

uint32_t os_get_tick_count( void ) {
	return xTaskGetTickCount();
}

void vApplicationIdleHook( void )
{

}

void vApplicationStackOverflowHook(TaskHandle_t xtask, char* pcTaskName)
{
  asm("bkpt");
}

void vApplicationMallocFailedHook(void)
{
  asm("bkpt");
}