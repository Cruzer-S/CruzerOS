#include "stdint.h"
#include "stdbool.h"

#include "hal_uart.h"
#include "hal_interrupt.h"
#include "hal_timer.h"

#include "stdio.h"
#include "stdlib.h"

static void hw_init(void);

static void print_test(void);
static void timer_test(void);

void main(void)
{
	hw_init();

	uint32_t i = 100;
	while ( i-- ) 
	{
		hal_uart_put_char('N');
	}
	hal_uart_put_char('\n');

	putstr("Hello World! \n");

	print_test();
	timer_test();

	while (true) ;
}

static void hw_init(void)
{
	hal_interrupt_init();
	hal_uart_init();
	hal_timer_init();
}

static void print_test(void)
{
	char *str = "print pointer test";
	char *nullptr = 0;
	uint32_t i = 5;
	uint32_t *sys_ctrl_0 = (uint32_t *)0x10001000;

	debug_printf("%s \n", "Hello printf");
	debug_printf("output string pointer: %s \n", str);
	debug_printf("%s is null pointer ,%u number \n", nullptr, 10);
	debug_printf("%u = 5 \n", i);
	debug_printf("dec = %u hex = %x \n", 0xff, 0xff);
	debug_printf("print zero %u \n", 0);

	debug_printf("SYSCTRL0 %x \n", *sys_ctrl_0);
}

static void timer_test(void)
{
	while (true)
	{
		debug_printf("current count : %u \n", hal_timer_get_1ms_counter());
		delay(1000);
	}
}
