#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "erm19264.h"

int main(void)
{
	glcd_Init();
	unsigned char i;
	glcd_Send_Command(CMD_SET_PAGE | 0x7, CTRL_LEFT);
	glcd_Send_Command(CMD_SET_COLUMN | 0x0, CTRL_LEFT);
	for (i=0; i<64; i++)
	{
		glcd_Write_Data(0x1, CTRL_LEFT);
		glcd_Set_Start_Line(i, CTRL_LEFT);
		_delay_ms(500);
	}
}
