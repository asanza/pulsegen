/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Sunday January 27th 2019
 * Author: diego
 */

#include <os/threads.h>
#include "FreeRTOS.h"
#include "task.h"

thread_t os_thread_new(const char* name, thread_fn thread,
    void* args, int stacksize, int priority){
    xTaskCreate(thread, name, stacksize, args, priority, NULL);
    return xTaskGetHandle(name);
}

void os_thread_delete(thread_t thread)
{
  vTaskDelete((TaskHandle_t)thread);
}

void os_thread_sleep(uint32_t ms) {
    vTaskDelay((ms) / portTICK_PERIOD_MS);
}

void os_thread_sleep_until(uint32_t* last_wake_time, uint32_t ms) {
	vTaskDelayUntil(last_wake_time, ms / portTICK_PERIOD_MS);
}

thread_t os_thread_get_handle(const char* name)
{
  return xTaskGetHandle(name);
}

thread_t os_thread_get_current( void )
{
  return xTaskGetCurrentTaskHandle();
}
