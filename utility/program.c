/*
 * File: program.c
 * Date: 03.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

volatile union program_type program;

const uint8_t flash_program[][PROGRAM_STORE_SIZE] = { /*волна*/{ 0, 0, 1, 4, 16, 64, 128, 128, 64, 16, 4, 1, 255, 255,
		255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0 }, /*семафор*/{ 1, 1, 1, 1, 1, 1, 32, 32, 32, 32, 32,
		32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 16, 10, 0, 1, 0 }, /*рябь*/{ 0, 0, 1, 4, 16, 64, 128, 128, 64,
		16, 4, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 3, 8, 0, 0, 0, 1, 0 }, /*мерцание*/{ 0,
		2, 8, 16, 32, 64, 64, 32, 16, 8, 2, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 2, 0, 0, 0,
		0, 1, 2 }, /*падающая звезда*/{ 0, 0, 1, 1, 2, 2, 4, 8, 16, 32, 64, 128, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 4, 0, 16, 0, 0, 1, 0 }, /*бугущие огни*/{ 0, 0, 0, 0, 128, 128, 0, 0, 0, 0, 128, 128,
		255, 255, 255, 255, 1, 1, 255, 255, 255, 255, 1, 1, 3, 0, 0, 10, 3, 0, 0 }, /*переливание*/{ 0, 0, 128, 128, 0,
		0, 128, 128, 0, 0, 128, 128, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 2, 8, 0, 0, 0, 0, 0 }, /*бегущие огни*/
{ 128, 0, 0, 128, 0, 0, 128, 0, 0, 128, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0,
		3, 0, 0 }, { 0, 1, 2, 4, 8, 16, 32, 64, 128, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 1, 0, 0, 0, 0, 0, 0 } };

volatile uint8_t slide_current;
volatile uint8_t slide_target;
volatile uint8_t slide_restore;
volatile uint8_t pwm_target;

//------------------------------------------------------------------------------
void do_work(void)
{
	uint8_t channel_number;
	uint8_t channel_bright;

	for (channel_number = 0; channel_number < ARRAY_LENGHT(program.channel_bright); channel_number++)
	{
		channel_bright = program.channel_bright[channel_number];

		if (program.channel_effect[channel_number] > 128)
		{
			// увеличение яркости
			if (channel_bright != 0)
			{
				channel_bright <<= 1;

				if (channel_bright == 0)
				{
					channel_bright = 128;

					program.channel_effect[channel_number] = 0;
				}
			}
			else
			{
				channel_bright = 1;
			}
		}

		if (program.channel_effect[channel_number] < 128)
		{
			// уменьшение яркости
			if (channel_bright != 0)
			{
				channel_bright >>= 1;
			}
			else
			{
				program.channel_effect[channel_number] = 255;
			}
		}

		program.channel_bright[channel_number] = channel_bright;
	}
}

//------------------------------------------------------------------------------
void do_jump(void)
{
	uint8_t channel_number;

	for (channel_number = 0; channel_number < ARRAY_LENGHT(program.channel_bright); channel_number++)
	{
		if (program.channel_effect[channel_number] != 128)
		{
			if (program.channel_bright[channel_number] == 0)
			{
				program.channel_bright[channel_number] = 128;
			}
			else
			{
				// уменьшаем яркость
				program.channel_bright[channel_number] >>= 1;
			}
		}
	}
}

//------------------------------------------------------------------------------
void do_strobo(void)
{
	uint8_t tmp;

	program.strobo_out = 8;

	tmp = get_random_byte();
	tmp &= 127;
	tmp |= 3;

	program.period_strobo = tmp;
}

//------------------------------------------------------------------------------
void do_slide(void)
{
	uint16_t tmp;

	if (slide_current == 128)
		return;

	if (slide_current > 127)
	{
		tmp = 128;
		tmp -= slide_current;
		tmp += 40;
		tmp += slide_restore;
		slide_restore = (uint8_t) tmp;
		if (tmp > 256)
		{
			if (program.slide > 0)
			{
				program.slide--;
			}
			else
			{
				program.slide = ARRAY_LENGHT(program.channel_bright) - 1;
			}
		}
	}
	else
	{
		tmp = slide_current;
		tmp -= 128;
		tmp += 40;
		tmp += slide_restore;
		slide_restore = (uint8_t) tmp;
		if (tmp > 256)
		{
			if (program.slide < (ARRAY_LENGHT(program.channel_bright) - 1))
			{
				program.slide++;
			}
			else
			{
				program.slide = 0;
			}
		}
	}
}

//------------------------------------------------------------------------------
void do_bright(void)
{
	if (program.pwm_max == pwm_target)
	{
		pwm_target -= get_random_byte();
		pwm_target |= 3;
	}
	if (program.pwm_max > pwm_target)
	{
		program.pwm_max--;
	}
	else
	{
		program.pwm_max++;
	}
}

//------------------------------------------------------------------------------
void do_blink(void)
{
	uint8_t channel_number;
	uint8_t channel_bright;

	for (channel_number = 0; channel_number < ARRAY_LENGHT(program.channel_bright); channel_number++)
	{
		channel_bright = program.channel_bright[channel_number];

		if (get_random_byte() < 128)
		{
			channel_bright >>= 1;
		}
		else
		{
			if (channel_bright == 0)
			{
				channel_bright = 128;
			}
			else
			{
				channel_bright <<= 1;
			}
		}

		program.channel_bright[channel_number] = channel_bright;
	}
}

//------------------------------------------------------------------------------
void do_eeprom_next(void)
{
}

//------------------------------------------------------------------------------
void do_flash_next(void)
{
}

//------------------------------------------------------------------------------
void do_slide_target(void)
{
	if (slide_current == slide_target)
	{
		slide_target -= get_random_byte();
	}

	if (slide_current > slide_target)
	{
		slide_current--;
	}
	if (slide_current < slide_target)
	{
		slide_current++;
	}
}

//------------------------------------------------------------------------------
void do_switch(void)
{
}

//------------------------------------------------------------------------------
void do_strobo_blinc(void)
{
	if (program.strobo_out != 0)
	{
		program.strobo_out--;
	}
}

//------------------------------------------------------------------------------
void program_init(void)
{
	uint8_t byte_number;

	for (byte_number = 0; byte_number < PROGRAM_STORE_SIZE; byte_number++)
	{
		program.raw[byte_number] = flash_program[0][byte_number];
	}

	program.period_strobo_blink = 6;
	program.period_slide_target = 20;
	program.period_switch = 50;
	program.pwm_max = 128;

	slide_current = 128;
}
