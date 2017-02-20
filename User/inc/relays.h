#ifndef _RELAYS_H
#define _RELAYS_H

void Relays_init(void);
void Relays_On(uint16_t relay_mask);
void Relays_Off(uint16_t relay_mask);
void Relays_AllOn(void);
void Relays_AllOff(void);

#endif