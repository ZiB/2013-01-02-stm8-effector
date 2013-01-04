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

	// выходы ВАМ модулятора
	PIN_CONFIGURATION(PIN_BAM_0);
	PIN_CONFIGURATION(PIN_BAM_1);
	PIN_CONFIGURATION(PIN_BAM_2);
	PIN_CONFIGURATION(PIN_BAM_3);
	PIN_CONFIGURATION(PIN_BAM_4);
	PIN_CONFIGURATION(PIN_BAM_5);
	PIN_CONFIGURATION(PIN_BAM_6);
	PIN_CONFIGURATION(PIN_BAM_7);
	PIN_CONFIGURATION(PIN_BAM_8);
	PIN_CONFIGURATION(PIN_BAM_9);
	PIN_CONFIGURATION(PIN_BAM_10);
	PIN_CONFIGURATION(PIN_BAM_11);

	// линии UART
	PIN_CONFIGURATION(PIN_UART_RX);
	PIN_CONFIGURATION(PIN_UART_TX);

	// после сброса микроконтроллер работает от встроенного HSI-генератора
	// с делителем по умолчанию 8, меняем его на 2, т.е. частота будет равна 16/2 = 8 МГц
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);

	// таймер для диспетчера задач
	TIM4_DeInit();
	TIM4_TimeBaseInit(TIM4_PRESCALER_32, 250 - 1); // 8МГц / 32 / 250 = 1 кГц
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	TIM4_Cmd(ENABLE);

	// таймер для ВАМ модулятора
	TIM2_DeInit();
	TIM2_TimeBaseInit(TIM2_PRESCALER_128, 1024 - 1);
	TIM2_ClearFlag(TIM2_FLAG_UPDATE);
	TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
	TIM2_Cmd(ENABLE);

	// инициализация UART
	mcu_uart1_fifo_init(9600);

	// инициализация программы эффектов
	program_init();

	// разрешаем прерывания
	enableInterrupts();

	// основной цикл
	while (1)
	{
		monitor_refresh();
	}
}
