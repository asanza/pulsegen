/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Wednesday January 30th 2019
 * Author: diego
 */

#ifndef BOARD_H
#define BOARD_H
#ifdef __cplusplus
extern "C"{
#endif

#include <hal/gpio.h>

#define POWER_HOLD GPIO_PORTB(1)
#define GREEN_LED  GPIO_PORTA(6)
#define RED_LED	   GPIO_PORTA(5)

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
