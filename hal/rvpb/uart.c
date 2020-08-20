#include "stdint.h"
#include "uart.h"
#include "hal_uart.h"
#include "hal_interrupt.h"

extern volatile PL011_t* uart;

static void interrupt_handler(void);

void hal_uart_init(void)
{
    // Enable UART
    uart->uartcr.bits.UARTEN = 0;
    uart->uartcr.bits.TXE = 1;
    uart->uartcr.bits.RXE = 1;
    uart->uartcr.bits.UARTEN = 1;

	uart->uartimsc.bits.RXIM = 1;

	hal_interrupt_enable(UART_INTERRUPT0);
	hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);
}

void hal_uart_put_char(uint8_t ch)
{
    while(uart->uartfr.bits.TXFF);
    uart->uartdr.all = (ch & 0xFF);
}

uint8_t hal_uart_get_char(void)
{
	uint32_t data;

	while (uart->uartfr.bits.RXFE);

	data = uart->uartdr.all;

	if (data & 0xFFFFFF00)
	{
		uart->uartrsr.all = 0xFF;
		return 0;
	}

	return (uint8_t)(data & 0xFF);
}

static void interrupt_handler(void)
{
	uint8_t ch = hal_uart_get_char();
	hal_uart_put_char(ch);
}

