#include "main.h"

int main(void)
{
  uint16_t i=1;
  Relays_init();
  Relays_AllOff();
  UART_init();
  while(i<16384)
  {
    Relays_On(i);
    i=i<<1;
  }
  while(i>0)
  {
    Relays_Off(i);
    i>>=1;
  }
  while(1)
  {
  
  }
}



//clock config
void HSE_start(void)
{
  RCC->CR |= (RCC_CR_CSSON|RCC_CR_HSEBYP|RCC_CR_HSEON);
  while(!(RCC->CIR & RCC_CIR_HSERDYF))
  {
    RCC->CIR |= RCC_CIR_HSERDYC;       //clear HSE ready flag
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_0;
  }
}