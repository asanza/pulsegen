/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday January 26th 2019
 * Author: diego
 */

#ifndef SYS_H
#define SYS_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

bool hal_sys_is_irq( void );

#ifdef __cplusplus
}
#endif

#endif /* SYS_H */
