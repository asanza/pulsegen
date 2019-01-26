/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef OS_THREADS_H
#define OS_THREADS_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

typedef void* thread_t;
typedef void (*thread_fn)(void*);

thread_t os_thread_new(const char* name, thread_fn thread,
    void* args, int stacksize, int priority);
void os_thread_sleep(uint32_t ms);
void os_thread_sleep_until(uint32_t* last_wake_time, uint32_t ms);
thread_t os_thread_get_handle(const char* thread_name);
thread_t os_thread_get_current( void );


#ifdef __cplusplus
}
#endif

#endif /* OS_THREADS_H */
