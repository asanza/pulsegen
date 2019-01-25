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

void os_init( void )
{
  vTaskStartScheduler();
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