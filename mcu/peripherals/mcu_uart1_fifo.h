/*
 *  File:   mcu_uart1_fifo.h
 *  Date:   26.05.2011
 *  Denis Zheleznjakov @ ZiBlog.ru
 */

#ifndef MCU_UART1_FIFO_H_
#define MCU_UART1_FIFO_H_

enum uart_fifo_size
{
	UART_TX_BUFFER_SIZE = 8, // кратен двум
	UART_RX_BUFFER_SIZE = 8 // кратен двум
};

enum uart_fifo_error
{
	UART_FIFO_ERROR_FRAME = BIT(0),
	UART_FIFO_ERROR_OVERRUN = BIT(1),
	UART_FIFO_ERROR_NOISE = BIT(2),
	UART_FIFO_ERROR_BUFFER_OVERFLOW = BIT(3),
	UART_FIFO_NO_DATA = BIT(4)
};

extern void mcu_uart1_fifo_init(uint32_t baud_rate);
extern uint8_t mcu_uart1_fifo_receive(uint8_t * data);
extern void mcu_uart1_fifo_tx_handler(void);
extern void mcu_uart1_fifo_rx_handler(void);
extern uint8_t mcu_uart1_fifo_receive(uint8_t * data);
extern void mcu_uart1_fifo_transmit(uint8_t data);
extern void mcu_uart1_set_baud_rate(uint16_t baud_rate);

#endif /* MCU_UART1_FIFO_H_ */
