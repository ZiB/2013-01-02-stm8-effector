/*
 *	File:	macros.c
 *	Date:	09.01.2012
 *	Denis Zheleznjakov @ ZiBlog.ru
 */

#include  "main.h"

static volatile uint16_t delay_count;
static volatile _Bool delay_flag;

//------------------------------------------------------------------------------
void delay_ms(volatile uint16_t delay)
{
	delay_count = delay;
	delay_flag = TRUE;

	while (delay_flag == TRUE)
	{
	}
}

//------------------------------------------------------------------------------
void delay_ms_refresh(void)
{
	if (delay_flag == TRUE)
	{
		if (--delay_count == 0U)
		{
			delay_flag = FALSE;
		}
	}
}
