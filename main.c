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

	// таймер для диспетчера задач
	TIM4_DeInit();
	TIM4_TimeBaseInit(TIM4_PRESCALER_32, 250 - 1); // 8МГц / 32 / 250 = 1 кГц
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	TIM4_Cmd(ENABLE);

	// разрешаем прерывания
	enableInterrupts();

	// основной цикл
	while (1)
	{
		PIN_ON(PIN_LED_GREEN);
		delay_ms(500);

		PIN_OFF(PIN_LED_GREEN);
		delay_ms(500);
	}
}
