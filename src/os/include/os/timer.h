/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef OS_TIMER_H
#define OS_TIMER_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <os/defs.h>

typedef void* os_timer_t;
typedef void (*os_timer_callback_fn)(os_timer_t timer);

os_timer_t os_timer_new(const char* name, uint32_t ms, bool reload, void* ctx,
    os_timer_callback_fn fn);
bool os_timer_start(os_timer_t timer);
bool os_timer_stop(os_timer_t timer);
void os_get_task_stats(char* json, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* OS_TIMER_H */
