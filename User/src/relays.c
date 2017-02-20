#include "main.h"


void Relays_init(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  
  //GPIOA->MODER = (uint32_t)0xF5555555;
  
  
  

  //GPIOA->MODER &= ~(GPIO_MODER_MODER15|GPIO_MODER_MODER14);
  GPIOA->MODER &= ~(
                      GPIO_MODER_MODER0|
                      GPIO_MODER_MODER1|
                      GPIO_MODER_MODER2|
                      GPIO_MODER_MODER3|
                      GPIO_MODER_MODER4|
                      GPIO_MODER_MODER5|
                      GPIO_MODER_MODER6|
                      GPIO_MODER_MODER7|
                      GPIO_MODER_MODER8|
                      GPIO_MODER_MODER11|
                      GPIO_MODER_MODER12
                    );
  GPIOA->MODER |= (
                      GPIO_MODER_MODER0_0|
                      GPIO_MODER_MODER1_0|
                      GPIO_MODER_MODER2_0|
                      GPIO_MODER_MODER3_0|
                      GPIO_MODER_MODER4_0|
                      GPIO_MODER_MODER5_0|
                      GPIO_MODER_MODER6_0|
                      GPIO_MODER_MODER7_0|
                      GPIO_MODER_MODER8_0|
                      GPIO_MODER_MODER11_0|
                      GPIO_MODER_MODER12_0
                  );

  GPIOA->OTYPER &=~ (GPIO_OTYPER_OT_0|
                     GPIO_OTYPER_OT_1|
                     GPIO_OTYPER_OT_2|
                     GPIO_OTYPER_OT_3|
                     GPIO_OTYPER_OT_4|
                     GPIO_OTYPER_OT_5|
                     GPIO_OTYPER_OT_6|
                     GPIO_OTYPER_OT_7|
                     GPIO_OTYPER_OT_8|
                     GPIO_OTYPER_OT_11|
                     GPIO_OTYPER_OT_12);
  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0|
                      GPIO_OSPEEDR_OSPEEDR1|
                      GPIO_OSPEEDR_OSPEEDR2|
                      GPIO_OSPEEDR_OSPEEDR3|
                      GPIO_OSPEEDR_OSPEEDR4|
                      GPIO_OSPEEDR_OSPEEDR5|
                      GPIO_OSPEEDR_OSPEEDR6|
                      GPIO_OSPEEDR_OSPEEDR7|
                      GPIO_OSPEEDR_OSPEEDR8|
                      GPIO_OSPEEDR_OSPEEDR11|
                      GPIO_OSPEEDR_OSPEEDR12);
  GPIOA->PUPDR &= ~(
                    GPIO_PUPDR_PUPDR0|
                    GPIO_PUPDR_PUPDR1|
                    GPIO_PUPDR_PUPDR2|
                    GPIO_PUPDR_PUPDR3|
                    GPIO_PUPDR_PUPDR4|
                    GPIO_PUPDR_PUPDR5|
                    GPIO_PUPDR_PUPDR6|
                    GPIO_PUPDR_PUPDR7|
                    GPIO_PUPDR_PUPDR8|
                    GPIO_PUPDR_PUPDR11|
                    GPIO_PUPDR_PUPDR12
                    );
  GPIOA->PUPDR |= ( GPIO_PUPDR_PUPDR0_1|
                    GPIO_PUPDR_PUPDR1_1|
                    GPIO_PUPDR_PUPDR2_1|
                    GPIO_PUPDR_PUPDR3_1|
                    GPIO_PUPDR_PUPDR4_1|
                    GPIO_PUPDR_PUPDR5_1|
                    GPIO_PUPDR_PUPDR6_1|
                    GPIO_PUPDR_PUPDR7_1|
                    GPIO_PUPDR_PUPDR8_1|
                    GPIO_PUPDR_PUPDR11_1|
                    GPIO_PUPDR_PUPDR12_1
                 );
  
  GPIOB->MODER &= ~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER6);
  GPIOB->MODER |= (GPIO_MODER_MODER0_1|GPIO_MODER_MODER1_1|GPIO_MODER_MODER6_1);
  GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0|GPIO_OTYPER_OT_1|GPIO_OTYPER_OT_6);
  GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0|GPIO_OSPEEDR_OSPEEDR1|GPIO_OSPEEDR_OSPEEDR6);
  GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR0|GPIO_PUPDR_PUPDR1|GPIO_PUPDR_PUPDR6);
  GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR0_1|GPIO_PUPDR_PUPDR1_1|GPIO_PUPDR_PUPDR6_1);
}


void Relays_On(uint16_t relay_mask)
{
  if(relay_mask > 256)
  {
    if(relay_mask & 512)
    {
      GPIOA->ODR |= GPIO_ODR_12;
      return;
    }
    if(relay_mask & 1024)
    {
      GPIOA->ODR |= GPIO_ODR_11;
      return;
    }  
    if(relay_mask & 2048)
    {
      GPIOB->ODR |= GPIO_ODR_6;
      return;
    }
    if(relay_mask & 4096)
    {
      GPIOB->ODR |= GPIO_ODR_1;
      return;
    }
    if(relay_mask & 8192)
    {
      GPIOB->ODR |= GPIO_ODR_0;
      return;
    }
  }
  else
  {
    GPIOA->ODR |= relay_mask;
  }
}


void Relays_Off(uint16_t relay_mask)
{
  if(relay_mask > 256)
  {
    if(relay_mask & 512)
    {
      GPIOA->ODR &= ~GPIO_ODR_12;
      return;
    }
    if(relay_mask & 1024)
    {
      GPIOA->ODR &= ~GPIO_ODR_11;
      return;
    }  
    if(relay_mask & 2048)
    {
      GPIOB->ODR &= ~GPIO_ODR_6;
      return;
    }
    if(relay_mask & 4096)
    {
      GPIOB->ODR &= ~GPIO_ODR_1;
      return;
    }
    if(relay_mask & 8192)
    {
      GPIOB->ODR &= ~GPIO_ODR_0;
      return;
    }
  }
  else
  {
    GPIOA->ODR &= ~relay_mask;
  }
}


void Relays_AllOn(void)
{
  GPIOA->ODR |= 0x19FF; //PA0-PA8,PA11,PA12
  GPIOB->ODR |= 0x43; //PB0-PB1
}


void Relays_AllOff(void)
{
  GPIOA->ODR &= ~0x19FF; //PA0-PA8,PA11,PA12
  GPIOB->ODR &= ~0x43;  //PB0-PB1,PB6
}


