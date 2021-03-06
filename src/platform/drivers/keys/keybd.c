#include <keybd.h>
#include "stm32f1xx_hal.h"

static key_handler_t keyfn;

static void manageEncoder( uint16_t pin ) {
    GPIO_PinState sa = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    GPIO_PinState sb = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);

    if ( sb != sa ) {
        keyfn(ENC_DEC);
    } else {
        keyfn(ENC_INC);
    }
}

void keybd_init(key_handler_t fn){
    GPIO_InitTypeDef   GPIO_InitStructure;

    /* Enable GPIOA clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* Configure PA0 pin as input floating */
    GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
                            | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStructure.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    keyfn = fn;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(keyfn != NULL) {
        switch(GPIO_Pin){
            case GPIO_PIN_8 : keyfn(KEY_TA1); break;
            case GPIO_PIN_9 : keyfn(KEY_TA2); break;
            case GPIO_PIN_10: keyfn(KEY_TA3); break;
            case GPIO_PIN_11: keyfn(KEY_TA4); break;
            case GPIO_PIN_12: keyfn(KEY_TA5); break;
            case GPIO_PIN_13: keyfn(KEY_POW); break;
            case GPIO_PIN_14: manageEncoder(GPIO_PIN_14); break;
            case GPIO_PIN_15: manageEncoder(GPIO_PIN_15); break;
        }
    }
}

void EXTI9_5_IRQHandler(void)
{
    uint16_t pin = EXTI->PR;
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_9);
}

void EXTI15_10_IRQHandler(void)
{
    uint16_t pin = EXTI->PR;
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(pin & GPIO_PIN_15);
}
