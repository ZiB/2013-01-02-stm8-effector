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

	// после сброса микроконтроллер работает от встроенного HSI-генератора
	// с делителем по умолчанию 8, меняем его на 2, т.е. частота будет равна 16/2 = 8 МГц
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);

	// основной цикл
	while (1)
	{
	}
}
