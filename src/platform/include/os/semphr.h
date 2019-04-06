/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef OS_SEMPHR_H
#define OS_SEMPHR_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <os/defs.h>

typedef void* os_semphr_t;
os_semphr_t os_semphr_new(uint8_t count);
bool os_semphr_wait(os_semphr_t sem, uint32_t ms);
bool os_semphr_signal(os_semphr_t sem);

#ifdef __cplusplus
}
#endif

#endif /* OS_SEMPHR_H */
