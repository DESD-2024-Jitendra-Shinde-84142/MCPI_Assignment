/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: jitendra
 */

#include "timer.h"


void TimerInit(uint32_t ms) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = TIM_PR-1;

	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM7->ARR = cnt - 1;

	TIM7->CNT = 0;

	TIM7->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM7_IRQn);

	TIM7->CR1 |= TIM_CR1_CEN;
}

int exti0_flag = 0;

void TIM7_IRQHandler(void)
{
	if(TIM7->SR & TIM_SR_UIF) {

		TIM7->SR &= ~TIM_SR_UIF;
		exti0_flag = 1;

	}
}




