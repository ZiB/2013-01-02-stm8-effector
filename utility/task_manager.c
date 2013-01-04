/*
 * File: task_manager.c
 * Date: 02.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

const void (* const task_list[11])(void) = { do_work, do_jump, do_strobo, do_slide, do_bright, do_blink,
		do_eeprom_next, do_flash_next, do_slide_target, do_switch, do_strobo_blinc };

//------------------------------------------------------------------------------
void task_manager_refresh(void)
{
	uint8_t task_number;
	uint8_t * period = &program.period_work;
	uint8_t * counter = &program.counter_work;

	for (task_number = 0; task_number < ARRAY_LENGHT(task_list); task_number++)
	{
		// проверка активности задачи
		if (period[task_number] != 0)
		{
			// проверка готовности выполенения
			if (++counter[task_number] >= period[task_number])
			{
				// сброс счетчика
				counter[task_number] = 0;

				// вызов задачи
				(*task_list[task_number])();
			}
		}
	}
}
