#include "main.h"

__IO uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
__IO uint8_t rx_byte_count = 0;
uint8_t cmdReceived = 0;


void UART_init(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  
  //TX pin PA9
  GPIOA->MODER |= GPIO_MODER_MODER9_1;
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT_9;
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;
  
  
  //RX pin PA10
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT_10;
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR10;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;
    
  GPIOA->AFR[1] |= (GPIO_AFRH_AFR9|GPIO_AFRH_AFR10);
  
  USART2->BRR  = 0x9c4;
  USART2->CR1 |= USART_CR1_RE;
  USART2->CR1 |= USART_CR1_TE;
  USART2->CR1 &= ~USART_CR1_M;  //8 bit
  USART2->CR1 &= ~USART_CR1_PS; //no parity control
  
  USART2->CR2 &=~ USART_CR2_STOP;//1 stop bit

  USART2->ISR &= ~USART_ISR_RXNE;
  USART2->CR1 |= USART_CR1_RXNEIE;
  NVIC_EnableIRQ (USART2_IRQn);
  USART2->CR1 |= USART_CR1_UE;
}


void UART_SendByte(uint8_t byte)
{
  while(!(USART2->ISR & USART_ISR_TC)); //∆дем пока бит TC в регистре ISR станет 1
  USART1->TDR=byte;                     //ќтсылаем байт через UART
}



