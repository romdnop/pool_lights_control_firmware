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
  GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;
  
  //RX pin PA10
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  GPIOA->OTYPER |= GPIO_OTYPER_OT_10;
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR10;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;
  GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;  
  
  GPIOA->AFR[1] |= 0x01 << (2*4);       //PA9-10 AF USART
  GPIOA->AFR[1] |= 0x01 << (1*4);


  //USART1->BRR  = 0x9c4;
  //USART1->BRR  = 0x2710;
  USART1->BRR = 0x1388; //9600 oversampling 16
  //USART1->BRR = 0x340;
  
  USART1->CR1 |= USART_CR1_RE;
  USART1->CR1 |= USART_CR1_TE;
  USART1->CR1 &= ~USART_CR1_M;  //8 bit
  USART1->CR1 &= ~USART_CR1_PS; //no parity control
  
  USART1->CR2 &=~ USART_CR2_STOP;//1 stop bit
  //USART1->CR2 |= USART_CR2_ABRMODE_1;
  
  USART1->CR1 |= USART_CR1_UE;
  USART1->ISR &= ~USART_ISR_RXNE;
  USART1->ISR &= ~USART_ISR_TXE;
  USART1->ISR &= ~USART_ISR_TC;
  USART1->CR1 |= USART_CR1_RXNEIE;
  //NVIC_EnableIRQ (USART1_IRQn);
  
}


void UART_SetBaudrate(uint16_t baud)
{
  
}



void UART_SendByte(uint8_t byte)
{
  while(!(USART1->ISR & USART_ISR_TC)); //∆дем пока бит TC в регистре ISR станет 1
  USART1->TDR=byte;                     //ќтсылаем байт через UART
}


