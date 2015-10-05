// ERM19264 driver library for Atmel AVR ATmega16

#include "erm19264.config.h"

#ifndef ERM19264_H_
#define ERM19264_H_

#define SCREEN_WIDTH	192
#define SCREEN_HEIGHT	64

#define CTRL_LEFT	0x0
#define CTRL_MIDDLE	0x1
#define CTRL_RIGHT	0x2
#define CTRL_DISABLE	0x3

#define MODE_CTRL_WRITE	0x0
#define MODE_STATUS_READ	0x1
#define MODE_DATA_WRITE	0x2
#define MODE_DATA_READ	0x3

#define CTRL_RS	_BV(PIN_RS)
#define CTRL_RW	_BV(PIN_RW)
#define CTRL_EN	_BV(PIN_EN)
#define CTRL_CSA	_BV(PIN_CSA)
#define CTRL_CSB	_BV(PIN_CSB)
#define CTRL_RESET	_BV(PIN_RESET)

#define ON	0x1
#define OFF	0x0
#define CMD_DISPLAY	0x3e
#define CMD_SET_COLUMN	0x40
#define CMD_SET_PAGE	0xb8
#define CMD_SET_DSL	0xc0

#define STATUS_BUSY	0x80
#define STATUS_POWER	0x20
#define STATUS_RESET	0x10

void glcd_Init(void);
void glcd_Send_Command(unsigned char, unsigned char);
void glcd_Write_Data(unsigned char, unsigned char);
unsigned char glcd_Read_Data(unsigned char);
void glcd_Set_Start_Line(unsigned char, unsigned char);
void glcd_Go_To(unsigned char, unsigned char, unsigned char);

#endif /* ERM19264_H_ */
