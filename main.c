/*
 * File: main.c
 * Date: 02.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

//------------------------------------------------------------------------------
void main(void)
{
	// запрет прерываний
	disableInterrupts();

	// перевод всех линий на вход с подтяжкой к плюсу
	GPIOA->CR1 = 0xFF;
	GPIOB->CR1 = 0xFF;
	GPIOC->CR1 = 0xFF;
	GPIOD->CR1 = 0xFF;
	GPIOE->CR1 = 0xFF;
	GPIOF->CR1 = 0xFF;

	// тестовый светодиод
	PIN_CONFIGURATION(PIN_LED_GREEN);

	PIN_ON(PIN_LED_GREEN);

	// основной цикл
	while (1)
	{
	}
}
