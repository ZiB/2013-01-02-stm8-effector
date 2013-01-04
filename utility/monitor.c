/*
 * File: monitor.c
 * Date: 04.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

uint8_t rx_key;

//------------------------------------------------------------------------------
void monitor_refresh(void)
{
	uint8_t rx_data;

	if (!(mcu_uart1_fifo_receive(&rx_data) & UART_FIFO_NO_DATA))
	{
		// управляющие символы
		if (rx_data < 48)
			return;

		// параметры
		if ((rx_data < 58) || (rx_data == 'U') || (rx_data == 'W') || (rx_data == 'Y'))
		{
			if (rx_key == 0)
				return;

			// яркость каналов
			if (rx_key < 'M')
			{
				rx_key -= 65;
				if (rx_key < ARRAY_LENGHT(program.channel_bright))
				{
					switch (rx_data)
					{
						case ('U'):
						{
							program.channel_effect[rx_key] = 255;
							break;
						}
						case ('Y'):
						{
							program.channel_effect[rx_key] = 128;
							break;
						}
						case ('W'):
						{
							program.channel_effect[rx_key] = 0;
							break;
						}
						default:
						{
							rx_data -= 48;
							if (rx_data-- == 0)
							{
								program.channel_bright[rx_key] = 0;
							}
							else
							{
								program.channel_bright[rx_key] = (uint8_t) BIT(rx_data);
							}
						}
					}
				}
			}
			else
			{
				// эффекты
				switch (rx_key)
				{
					case ('S'):
					{
						program.speed = (uint8_t) (rx_data - 48);

						break;
					}
					case ('N'):
					{
						if (rx_data == '0')
						{
							program.period_blink = 0;
						}
						if (rx_data == '1')
						{
							program.period_blink = 2;
						}

						break;
					}
					case ('T'):
					{
						if (rx_data == '0')
						{
							program.pwm_max = 128;
							program.period_bright = 0;
						}
						if (rx_data == '1')
						{
							program.period_bright = 1;
						}

						break;
					}
					case ('V'):
					{
						if (rx_data == '0')
						{
							program.slide = 0;
							program.period_slide = 0;
						}
						if (rx_data == '1')
						{
							program.period_slide = 3;
						}

						break;
					}
					case ('R'):
					{
						if (rx_data == '0')
						{
							program.period_work = 0;
						}
						if (rx_data == '1')
						{
							program.period_work = 8;
						}

						break;
					}
					case ('M'):
					{
						if (rx_data == '0')
						{
							program.period_jump = 0;
						}
						if (rx_data == '1')
						{
							program.period_jump = 16;
						}

						break;
					}
					case ('O'):
					{
						if (rx_data == '0')
						{
							program.strobo_out = 0;
							program.period_strobo = 0;
						}
						if (rx_data == '1')
						{
							program.period_strobo = 10;
						}

						break;
					}
				}
			}

			// сброс ключа
			rx_key = 0;

			return;
		}

		// не используемые символы
		if (rx_data >= 91)
			return;

		// получен ключ
		rx_key = rx_data;

	}
}
