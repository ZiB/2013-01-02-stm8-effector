/*
 * File: program.h
 * Date: 03.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#define PROGRAM_STORE_SIZE (12 + 12 + 7)

union program_type
{
	volatile uint8_t raw[PROGRAM_STORE_SIZE + 16];
	struct
	{
		// сохраняемая часть
		volatile uint8_t channel_bright[12];
		volatile uint8_t channel_effect[12];
		volatile uint8_t speed;
		volatile uint8_t period_work;
		volatile uint8_t period_jump;
		volatile uint8_t period_strobo;
		volatile uint8_t period_slide;
		volatile uint8_t period_bright;
		volatile uint8_t period_blink;
		// несохраняемая часть
		volatile uint8_t period_eeprom_next;
		volatile uint8_t period_flash_next;
		volatile uint8_t period_slide_target;
		volatile uint8_t period_switch;
		volatile uint8_t period_strobo_blink;
		volatile uint8_t counter_work;
		volatile uint8_t counter_jump;
		volatile uint8_t counter_strobo;
		volatile uint8_t counter_slide;
		volatile uint8_t counter_bright;
		volatile uint8_t counter_blink;
		volatile uint8_t counter_eeprom_next;
		volatile uint8_t counter_flash_next;
		volatile uint8_t counter_slide_target;
		volatile uint8_t counter_switch;
		volatile uint8_t counter_strobo_blink;
		volatile uint8_t slide;
		volatile uint8_t pwm_max;
		volatile uint8_t strobo_out;
	};
};

extern union program_type program;

void program_init(void);
void do_work(void);
void do_jump(void);
void do_strobo(void);
void do_slide(void);
void do_bright(void);
void do_blink(void);
void do_eeprom_next(void);
void do_flash_next(void);
void do_slide_target(void);
void do_switch(void);
void do_strobo_blinc(void);

#endif /* PROGRAM_H_ */
