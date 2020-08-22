#include "stdint.h"
#include "stdbool.h"

#include "hal_uart.h"
#include "hal_interrupt.h"
#include "hal_timer.h"

#include "stdio.h"
#include "stdlib.h"

#include "task.h"

static void hw_init(void);
static void kernel_init(void);

static void print_test(void);
static void timer_test(void);

void user_task_0(void);
void user_task_1(void);
void user_task_2(void);

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

static void kernel_init(void)
{
	uint32_t task_id;

	kernel_task_init();

	task_id = kernel_task_create(user_task_0);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_0 creation fail \n");

	task_id = kernel_task_create(user_task_1);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_1 creation fail \n");

	task_id = kernel_task_create(user_task_2);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_2 creation fail \n");
}

void user_task_0(void)
{
	debug_printf("User Task #0 \n");

	while (true) ;
}

void user_task_1(void)
{
	debug_printf("User Task #1 \n");

	while (true) ;
}

void user_task_2(void)
{
	debug_printf("User Task #2 \n");

	while (true) ;
}
