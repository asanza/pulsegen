/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Friday January 25th 2019
 * Author: diego
 */

#ifndef OS_H
#define OS_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>

void os_start( void );

void os_enter_critical( void );
void os_exit_critical( void );
uint32_t os_get_tick_count( void );

#ifdef __cplusplus
}
#endif
#endif /* OS_H */
