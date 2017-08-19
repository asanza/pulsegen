#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

static TIM_HandleTypeDef        hTIM6;
static uint32_t                 uwIncrementState = 0;

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;

  /*Configure the TIM6 IRQ priority */
  HAL_NVIC_SetPriority(TIM6_IRQn, TickPriority ,0);

  /* Enable the TIM6 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM6_IRQn);

  /* Enable TIM6 clock */
  __HAL_RCC_TIM6_CLK_ENABLE();

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

  /* Compute TIM6 clock */
  uwTimclock = HAL_RCC_GetPCLK2Freq();

  /* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);

  /* Initialize TIM6 */
  hTIM6.Instance = TIM6;

  /* Initialize TIMx peripheral as follow:
  + Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  hTIM6.Init.Period = (1000000 / 1000) - 1;
  hTIM6.Init.Prescaler = uwPrescalerValue;
  hTIM6.Init.ClockDivision = 0;
  hTIM6.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&hTIM6) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    return HAL_TIM_Base_Start_IT(&hTIM6);
  }

  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM6 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable TIM6 update Interrupt */
  __HAL_TIM_DISABLE_IT(&hTIM6, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM6 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM6 Update interrupt */
  __HAL_TIM_ENABLE_IT(&hTIM6, TIM_IT_UPDATE);
}

void TIM6_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&hTIM6);
  HAL_IncTick();
}
