// ERM19264 driver library for Atmel AVR ATmega16

#include <avr/io.h>
#include <util/delay.h>
#include "erm19264.h"

void glcd_Set_Mode(unsigned char mode)
{
	switch (mode){
		case MODE_CTRL_WRITE:
			DATA_DIR = 0xff;
			CTRL_PORT &= ~(CTRL_RS|CTRL_RW);
			break;
		case MODE_STATUS_READ:
			DATA_DIR = 0x00;
			CTRL_PORT &= ~CTRL_RS;
			CTRL_PORT |= CTRL_RW;
			break;
		case MODE_DATA_WRITE:
			DATA_DIR = 0xff;
			CTRL_PORT |= CTRL_RS;
			CTRL_PORT &= ~CTRL_RW;
			break;
		case MODE_DATA_READ:
			DATA_DIR = 0x00;
			CTRL_PORT |= (CTRL_RS|CTRL_RW);
			break;
		default:
			break;
	}
}

void glcd_Set_Controller(unsigned char controller)
{
	switch (controller){
		case CTRL_LEFT:
			CTRL_PORT &= ~(CTRL_CSA|CTRL_CSB);
			break;
		case CTRL_MIDDLE:
			CTRL_PORT |= CTRL_CSA;
			CTRL_PORT &= ~CTRL_CSB;
			break;
		case CTRL_RIGHT:
			CTRL_PORT &= ~CTRL_CSA;
			CTRL_PORT |= CTRL_CSB;
			break;
		case CTRL_DISABLE:
			CTRL_PORT |= (CTRL_CSA|CTRL_CSB);
			break;
		default:
			break;
	}
}

void glcd_Tick(void)
{
	CTRL_PORT |= CTRL_EN;
	_delay_us(1);
	CTRL_PORT &= ~CTRL_EN;
}

unsigned char glcd_Read_Status(unsigned char controller)
{
	unsigned char status;
	glcd_Set_Controller(controller);
	glcd_Set_Mode(MODE_STATUS_READ);
	CTRL_PORT |= CTRL_EN;
	_delay_us(1);
	status = DATA_PIN;
	CTRL_PORT &= ~CTRL_EN;
	glcd_Set_Controller(CTRL_DISABLE);
	return status;
}

unsigned char glcd_Read_Data(unsigned char controller)
{
	unsigned char data;
	glcd_Set_Controller(controller);
	glcd_Set_Mode(MODE_DATA_READ);
	CTRL_PORT |= CTRL_EN;
	_delay_us(1);
	data = DATA_PIN;
	CTRL_PORT &= ~CTRL_EN;
	glcd_Set_Controller(CTRL_DISABLE);
	return data;
}

void glcd_Write_Data(unsigned char data, unsigned char controller)
{
	while(glcd_Read_Status(controller)&STATUS_BUSY);
	glcd_Set_Controller(controller);
	glcd_Set_Mode(MODE_DATA_WRITE);
	DATA_PORT = data;
	glcd_Tick();
	glcd_Set_Controller(CTRL_DISABLE);
}

void glcd_Send_Command(unsigned char command, unsigned char controller)
{
	while(glcd_Read_Status(controller)&STATUS_BUSY);
	glcd_Set_Controller(controller);
	glcd_Set_Mode(MODE_CTRL_WRITE);
	DATA_PORT = command;
	glcd_Tick();
	glcd_Set_Controller(CTRL_DISABLE);
}

void glcd_Go_To(unsigned char page, unsigned char column, unsigned char controller)
{
	glcd_Send_Command(CMD_SET_PAGE | page, controller);
	glcd_Send_Command(CMD_SET_COLUMN | column, controller);
}

void glcd_Set_Start_Line(unsigned char startline, unsigned char controller)
{
	glcd_Send_Command(CMD_SET_DSL | startline, controller);
}

void glcd_Power(unsigned char action)
{
	unsigned char i;
	for(i = 0; i < 3; i++)
		glcd_Send_Command((CMD_DISPLAY|action), i);
}

void glcd_Reset(void)
{
	CTRL_PORT &= ~CTRL_RESET;
	_delay_us(1);
	CTRL_PORT |= CTRL_RESET;
}

void glcd_Init(void)
{
	CTRL_DIR |= (CTRL_RW|CTRL_RS|CTRL_EN|CTRL_CSA|CTRL_CSB|CTRL_RESET);
	glcd_Power(ON);
	glcd_Reset();
}
