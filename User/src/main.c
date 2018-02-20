#include "main.h"


uint8_t RData = 0;
volatile uint16_t OverflowCount = 0;
void LED_Init(void);
void Watchdog_init(void);
void Watchdog_reset(void);

int main(void)
{
  
  uint8_t Relay = 0, RelayState = 0;
  SystemInit();
  UART_init();
  Relays_init();
  Relays_AllOff();
  //Relays_AllOn();
  
  //LED_Init();
  Timer_init();
  __enable_irq();
  Watchdog_init();
  UART_SendByte(220);
  while(1)
  {
    Watchdog_reset();
    if(USART1->ISR & USART_ISR_RXNE)
    {
      USART1->ISR &=~ USART_ISR_RXNE;
      RData = USART1->RDR;
      if(RData == 220)
      {
        //Reset timer count
        OverflowCount=0;
      }
      else
      {
        Relay = RData/10;
        RelayState = RData - Relay*10;
        if(Relay>22)Relay--;
        if(Relay != 0)
        {
          if(RelayState == 5)Relays_SetRelayState(Relay,0);
          if(RelayState == 0)Relays_SetRelayState(Relay,1);
        }
      }
      UART_SendByte(RData);
    }
    if(OverflowCount > 27) //~3min (old=2)
    {
      Relays_AllOff();
    }
  }
}



//clock config
void HSE_start(void)
{
  RCC->CR |= (RCC_CR_CSSON|RCC_CR_HSEBYP|RCC_CR_HSEON);
  while(~(RCC->CIR & RCC_CIR_HSERDYF)); //wait for HSE
  
  RCC->CIR |= RCC_CIR_HSERDYC;       //clear HSE ready flag
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_0;
}

void Watchdog_init(void)
{
  IWDG->KR = (uint16_t)0xCCCC;
  //(uint16_t)0x5555
  IWDG->KR = IWDG_KR_KEY;
  IWDG->PR = IWDG_PR_PR;//set prescaler = 7
  IWDG->RLR = (uint32_t)0x00000FFF;
  while(IWDG->SR);
  
  IWDG->KR = (uint32_t)0x0000AAAA;
}

void Watchdog_reset(void)
{
  IWDG->KR = (uint32_t)0x0000AAAA;
}

void LED_Init(void)
{
  GPIOB->MODER &= ~(GPIO_MODER_MODER3);
  GPIOB->MODER |= (GPIO_MODER_MODER3_0);
  GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_3);
  GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR3);
  GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR3);
  GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR3_1);
  GPIOB->ODR |= GPIO_ODR_3;
}


//each 10 sec, see Timer_init() in "timer.c"
void TIM16_IRQHandler(void)
{
  if(TIM16->SR & TIM_SR_UIF)
  {
    TIM16->SR &= ~TIM_SR_UIF;
    OverflowCount++;
  }
}


void USART1_IRQHandler(void)
{
  if(USART1->ISR & USART_ISR_RXNE)
  {
    USART1->ISR &=~ USART_ISR_RXNE;
  }
}




