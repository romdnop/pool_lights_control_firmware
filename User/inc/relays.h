#ifndef _RELAYS_H
#define _RELAYS_H


#define PRELAY1 GPIOA
#define RELAY1  GPIO_ODR_12
#define PRELAY2 GPIOA
#define RELAY2  GPIO_ODR_6
#define PRELAY3 GPIOA
#define RELAY3  GPIO_ODR_11
#define PRELAY4 GPIOA
#define RELAY4  GPIO_ODR_5
#define PRELAY5 GPIOA
#define RELAY5  GPIO_ODR_8
#define PRELAY6 GPIOA
#define RELAY6  GPIO_ODR_4
#define PRELAY7 GPIOB
#define RELAY7  GPIO_ODR_6
#define PRELAY8 GPIOA
#define RELAY8  GPIO_ODR_3
#define PRELAY9 GPIOB
#define RELAY9  GPIO_ODR_1
#define PRELAY10 GPIOA
#define RELAY10  GPIO_ODR_2
#define PRELAY11 GPIOB
#define RELAY11  GPIO_ODR_0
#define PRELAY12 GPIOA
#define RELAY12  GPIO_ODR_1
#define PRELAY13 GPIOA
#define RELAY13  GPIO_ODR_7
#define PRELAY14 GPIOA
#define RELAY14  GPIO_ODR_0

#define SET_BIT(PORT,PIN)   PORT->ODR|=PIN
#define RESET_BIT(PORT,PIN) PORT->ODR&=~PIN


void Relays_init(void);
void Relays_On(uint16_t relay_mask);
void Relays_Off(uint16_t relay_mask);
void Relays_SetRelayState(uint8_t, uint8_t);
void Relays_AllOn(void);
void Relays_AllOff(void);

#endif