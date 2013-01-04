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

//------------------------------------------------------------------------------
void do_work(void)
{
}

//------------------------------------------------------------------------------
void do_jump(void)
{
}

//------------------------------------------------------------------------------
void do_strobo(void)
{
}

//------------------------------------------------------------------------------
void do_slide(void)
{
}

//------------------------------------------------------------------------------
void do_bright(void)
{
}

//------------------------------------------------------------------------------
void do_blink(void)
{
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
}

//------------------------------------------------------------------------------
void do_switch(void)
{
}

//------------------------------------------------------------------------------
void do_strobo_blinc(void)
{
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
}