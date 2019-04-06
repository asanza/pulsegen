/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef OS_QUEUE_H
#define OS_QUEUE_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <os/defs.h>

typedef void* os_queue_t;

os_queue_t os_queue_new(uint32_t len, uint32_t item_size);
bool os_queue_post(os_queue_t queue, void* message, uint32_t timeout);
bool os_queue_fetch(os_queue_t queue, void* message, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* OS_QUEUE_H */
