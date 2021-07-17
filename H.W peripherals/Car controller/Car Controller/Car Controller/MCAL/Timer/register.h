/*
 * register.h
 *
 * Created: 7/14/2021 11:57:39 AM
 *  Author: Shady Mamdouh
 */ 


#ifndef REGISTER_H_
#define REGISTER_H_

#define PORTA *((volatile uint8_t*)0x3B)
#define DDRA *(( volatile uint8_t*)0x3A)
#define PINA *((volatile uint8_t*)0x39)

#define PORTB *(( volatile uint8_t*)0x38)
#define DDRB *(( volatile uint8_t*)0x37)
#define PINB *((volatile uint8_t*)0x36)

#define PORTC *(( volatile uint8_t*)0x35)
#define DDRC *(( volatile uint8_t*)0x34)
#define PINC *((volatile uint8_t*)0x33)

#define PORTD *(( volatile uint8_t*)0x32)
#define DDRD *(( volatile uint8_t*)0x31)
#define PIND *((volatile uint8_t*)0x30)

#define TCNT0 *((volatile uint8_t*)0x52)
#define TCCR0 *((volatile uint8_t*)0x53)
#define OCR0 *((volatile uint8_t*)0x5C)
#define TIMSK *((volatile uint8_t*)0x59)
#define TIFR *((volatile uint8_t*)0x58)
#define SREG *((volatile uint8_t*)0x5F)
#endif /* REGISTER_H_ */