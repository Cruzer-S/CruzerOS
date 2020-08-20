#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

#include "hal_uart.h"
#include "hal_interrupt.h"

static void hw_init(void);
static void print_test(void);

void main(void)
{
	hw_init();

	uint32_t i = 100;
	while ( i-- ) {
		hal_uart_put_char('N');
	}
	hal_uart_put_char('\n');

	putstr("Hello World! \n");

	print_test();

	while (true) ;
}

static void hw_init(void)
{
	hal_interrupt_init();
	hal_uart_init();
}

static void print_test(void)
{
	char *str = "print pointer test";
	char *nullptr = 0;
	uint32_t i = 5;

	debug_printf("%s \n", "Hello printf");
	debug_printf("output string pointer: %s \n", str);
	debug_printf("%s is null pointer ,%u number \n", nullptr, 10);
	debug_printf("%u = 5 \n", i);
	debug_printf("dec = %u hex = %x \n", 0xff, 0xff);
	debug_printf("print zero %u \n", 0);

}
