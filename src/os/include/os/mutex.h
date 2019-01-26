/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef OS_MUTEX_H
#define OS_MUTEX_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <os/defs.h>

typedef void* os_mutex_t;
bool os_mutex_lock(os_mutex_t mutex, uint32_t timeout);
os_mutex_t os_mutex_new( void );
void os_mutex_unlock(os_mutex_t mutex);


#ifdef __cplusplus
}
#endif

#endif /* OS_MUTEX_H */
