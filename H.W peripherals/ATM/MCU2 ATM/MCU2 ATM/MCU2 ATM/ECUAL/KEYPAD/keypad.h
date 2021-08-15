/*
 * keypad.h
 *
 * Created: 4/25/2021 8:53:13 PM
 *  Author: Shady mamdouh
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
/******** keypad ports ***************/
#define keypadROWS_port PORT_B
#define keypadColumns_port PORT_D
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7
// APIs 
void keyPad_init(void);
uint8_t keyPad_GetKey(void);

#endif /* KEYPAD_H_ */