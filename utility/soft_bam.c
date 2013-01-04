/*
 * File: soft_bam.c
 * Date: 04.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

static volatile uint8_t bam_mask = 64;

//------------------------------------------------------------------------------
#define SOFT_PWM_CHANNEL(pwm_channel_number) \
{ \
	if(channel_number >= ARRAY_LENGHT(program.channel_bright)) \
	{ channel_number = 0; } \
	channel_bright = program.channel_bright[channel_number++];\
	if(channel_bright-- != 0) \
	{ \
		if ((bam_mask & channel_bright) && (channel_bright < program.pwm_max)) \
		{ PIN_ON(PIN_BAM_##pwm_channel_number); } \
		else \
		{ PIN_OFF(PIN_BAM_##pwm_channel_number); } \
	} \
	else { PIN_OFF(PIN_BAM_##pwm_channel_number); } \
}

//------------------------------------------------------------------------------
void soft_bam_refresh(void)
{
	uint8_t channel_bright = (uint8_t) (program.pwm_max >> 2);
	uint8_t channel_bright_max;
	uint16_t timer_value;
	uint8_t channel_number = program.slide;

	// пересчет периода
	bam_mask /= 2;
	if (bam_mask == 0)
	{
		bam_mask = 64;
	}

	// установка периода
	timer_value = bam_mask;
	timer_value *= 8;
	TIM2->ARRH = (uint8_t) (timer_value >> 8);
	TIM2->ARRL = (uint8_t) (timer_value);

	//
	if (program.strobo_out & BIT(0))
	{
		PIN_OFF(PIN_BAM_0);
		PIN_OFF(PIN_BAM_1);
		PIN_OFF(PIN_BAM_2);
		PIN_OFF(PIN_BAM_3);
		PIN_OFF(PIN_BAM_4);
		PIN_OFF(PIN_BAM_5);
		PIN_OFF(PIN_BAM_6);
		PIN_OFF(PIN_BAM_7);
		PIN_OFF(PIN_BAM_8);
		PIN_OFF(PIN_BAM_9);
		PIN_OFF(PIN_BAM_10);
		PIN_OFF(PIN_BAM_11);
	}
	else
	{
		SOFT_PWM_CHANNEL(0);
		SOFT_PWM_CHANNEL(1);
		SOFT_PWM_CHANNEL(2);
		SOFT_PWM_CHANNEL(3);
		SOFT_PWM_CHANNEL(4);
		SOFT_PWM_CHANNEL(5);
		SOFT_PWM_CHANNEL(6);
		SOFT_PWM_CHANNEL(7);
		SOFT_PWM_CHANNEL(8);
		SOFT_PWM_CHANNEL(9);
		SOFT_PWM_CHANNEL(10);
		SOFT_PWM_CHANNEL(11);
	}
}
