/*
 * File: mcu_uart1_fifo.c
 * Date: 02.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

struct
{
	volatile uint8_t rx_last_error;
	volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
	volatile uint8_t rx_buffer_head;
	volatile uint8_t rx_buffer_tail;
	volatile uint8_t tx_buffer[UART_TX_BUFFER_SIZE];
	volatile uint8_t tx_buffer_head;
	volatile uint8_t tx_buffer_tail;
} uart_fifo;

//------------------------------------------------------------------------------
void mcu_uart1_fifo_init(uint32_t baud_rate)
{
	uart_fifo.rx_buffer_head = 0;
	uart_fifo.rx_buffer_tail = 0;
	uart_fifo.tx_buffer_head = 0;
	uart_fifo.tx_buffer_tail = 0;

	UART1_DeInit();

	UART1_Init(baud_rate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,
			UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE,
			UART1_MODE_TXRX_ENABLE);

	UART1_ITConfig(UART1_IT_RXNE, ENABLE);

	UART1_Cmd(ENABLE);
}

//------------------------------------------------------------------------------
uint8_t mcu_uart1_fifo_receive(uint8_t * data)
{
	uint8_t rx_head;
	uint8_t rx_tail;

	rx_head = uart_fifo.rx_buffer_head;

	if (rx_head == uart_fifo.rx_buffer_tail)
		return UART_FIFO_NO_DATA;

	rx_tail = (uint8_t) ((uart_fifo.rx_buffer_tail + 1)
			& (uint8_t) (UART_RX_BUFFER_SIZE - 1));

	uart_fifo.rx_buffer_tail = rx_tail;

	*data = uart_fifo.rx_buffer[rx_tail];

	return uart_fifo.rx_last_error;
}

//------------------------------------------------------------------------------
void mcu_uart1_fifo_transmit(uint8_t data)
{
	uint8_t tx_head;

	tx_head = (uint8_t) ((uart_fifo.tx_buffer_head + 1)
			& (uint8_t) (UART_TX_BUFFER_SIZE - 1));

	while (tx_head == uart_fifo.tx_buffer_tail)
	{
	}

	uart_fifo.tx_buffer[tx_head] = data;
	uart_fifo.tx_buffer_head = tx_head;

	UART1->CR2 |= UART1_CR2_TIEN;
}

//------------------------------------------------------------------------------
void mcu_uart1_fifo_tx_handler(void)
{
	uint8_t status;
	uint8_t tx_tail;
	uint8_t tx_head;

	status = UART1->SR;

	if (status & UART1_SR_TC)
	{
		UART1->SR &= (uint8_t) (~UART1_SR_TC);
	}

	if (status & UART1_SR_TXE)
	{
		tx_head = uart_fifo.tx_buffer_head;
		tx_tail = uart_fifo.tx_buffer_tail;

		if (tx_head != tx_tail++)
		{
			tx_tail &= UART_TX_BUFFER_SIZE - 1;

			uart_fifo.tx_buffer_tail = tx_tail;
			UART1->DR = uart_fifo.tx_buffer[tx_tail];
		}
		else
		{
			UART1->CR2 &= (uint8_t) (~UART1_CR2_TIEN);
		}
	}
}

//------------------------------------------------------------------------------
void mcu_uart1_fifo_rx_handler(void)
{
	uint8_t status;
	uint8_t rx_data;
	uint8_t rx_last_error;
	uint8_t rx_head;

	status = UART1->SR;
	rx_data = UART1->DR;
	rx_last_error = 0;

	if (status & UART1_SR_FE)
		rx_last_error |= UART_FIFO_ERROR_FRAME;

	if (status & UART1_SR_OR)
		rx_last_error |= UART_FIFO_ERROR_OVERRUN;

	if (status & UART1_SR_NF)
		rx_last_error |= UART_FIFO_ERROR_NOISE;

	rx_head = (uint8_t) ((uart_fifo.rx_buffer_head + 1)
			& (uint8_t) (UART_RX_BUFFER_SIZE - 1));

	if (rx_head == uart_fifo.rx_buffer_tail)
	{
		rx_last_error |= UART_FIFO_ERROR_BUFFER_OVERFLOW;
	}
	else
	{
		uart_fifo.rx_buffer_head = rx_head;
		uart_fifo.rx_buffer[rx_head] = rx_data;
	}

	uart_fifo.rx_last_error = rx_last_error;
}
