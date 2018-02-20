#include "main.h"

void Timer_init(void)
{
  //Инициализация таймера на прерывание по переполнению
  RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
  
  
  TIM16->PSC = 0x7D00; //0d32000 for 1kHz
  TIM16->ARR = 0x2710;  //each second 0d10000
  TIM16->CNT = 0;

  TIM16->DIER |= TIM_DIER_UIE;  
  TIM16->CR1 |= TIM_CR1_CEN;
  
  NVIC_EnableIRQ(TIM16_IRQn);
  NVIC_SetPriority(TIM16_IRQn,0);
}

