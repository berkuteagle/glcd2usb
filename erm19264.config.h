// ERM19264 driver library for Atmel AVR ATmega16

#ifndef ERM19264_CONFIG_H_
#define ERM19264_CONFIG_H_

#define DATA_PORT	PORTC
#define DATA_DIR	DDRC
#define DATA_PIN	PINC
#define CTRL_PORT	PORTA
#define CTRL_DIR	DDRA
#define CTRL_PIN	PINA

#define PIN_RW	PIN0
#define PIN_RS	PIN1
#define PIN_EN	PIN2

#define PIN_CSA	PIN3
#define PIN_CSB	PIN4
#define PIN_RESET	PIN4

#endif /* ERM19264_CONFIG_H_ */
