#include "stdint.h"
#include "stdbool.h"

#include "hal_uart.h"
#include "hal_interrupt.h"
#include "hal_timer.h"

#include "stdio.h"
#include "stdlib.h"
#include "memio.h"

#include "kernel.h"
#include "event.h"
#include "message.h"

static uint32_t shared_value;
static void test_critical_section(uint32_t p, uint32_t task_id);

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

	kernel_init();

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
	for (uint32_t i = 0; i < 1; i++)
	{
		debug_printf("current count : %u \n", hal_timer_get_1ms_counter());
		delay(1000);
	}
}

static void kernel_init(void)
{
	uint32_t task_id;

	kernel_task_init();
	kernel_event_flag_init();
	kernel_sem_init(1);

	task_id = kernel_task_create(user_task_0);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_0 creation fail \n");

	task_id = kernel_task_create(user_task_1);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_1 creation fail \n");

	task_id = kernel_task_create(user_task_2);
	if (task_id == NOT_ENOUGH_TASK_NUM)
		putstr("task_2 creation fail \n");

	kernel_start();
}

void user_task_0(void)
{
	uint32_t local = 0;

	debug_printf("User Task #0 SP=0x%x\n", &local);

	uint8_t cmd_buf[16];
	uint32_t cmd_buf_idx = 0;
	uint8_t uart_ch;

	while (true)
	{
		kernel_event_flag_t handle_event 
			= kernel_wait_events (kernel_event_flag_uart_in | kernel_event_flag_cmd_out);

		switch (handle_event)
		{
		case kernel_event_flag_uart_in:
			kernel_receive_message(kernel_message_task_00, &uart_ch, 1);
			if (uart_ch == '\r')
			{
				cmd_buf[cmd_buf_idx] = '\0';

				kernel_send_message(kernel_message_task_01, &cmd_buf_idx, 1);
				kernel_send_message(kernel_message_task_01, cmd_buf, cmd_buf_idx);

				kernel_send_events(kernel_event_flag_cmd_in);

				cmd_buf_idx = 0;
			} else {
				cmd_buf[cmd_buf_idx] = uart_ch;
				cmd_buf_idx++;
				cmd_buf_idx %= 16;

				hal_uart_put_char(uart_ch);
			}

			break;

		case kernel_event_flag_cmd_out:
			test_critical_section(5, 0);
			break;
		}

		kernel_yield();
	}
}

void user_task_1(void)
{
	uint32_t local = 0;

	debug_printf("User Task #0 SP=0x%x\n", &local);

	uint8_t cmd_len = 0;
	uint8_t cmd[16] = { 0 };

	while (true)
	{
		kernel_event_flag_t handle_event 
			= kernel_wait_events(kernel_event_flag_cmd_in | kernel_event_flag_unlock);

		switch (handle_event)
		{
		case kernel_event_flag_cmd_in:
			memclr(cmd, 16);

			kernel_receive_message(kernel_message_task_01, &cmd_len, 1);
			kernel_receive_message(kernel_message_task_01, &cmd, cmd_len);

			debug_printf("Receive Command: %s \n", cmd);
			break;

		case kernel_event_flag_unlock:
			kernel_unlock_mutex();
			break;
		}

		kernel_yield();
	}
}

void user_task_2(void)
{
	uint32_t local = 0;

	debug_printf("User Task #0 SP=0x%x\n", &local);
	while (true)
	{
		test_critical_section(3, 2);
		kernel_yield();
	}
}

static void test_critical_section(uint32_t p, uint32_t task_id)
{
	// kernel_lock_sem();
	kernel_lock_mutex();

	debug_printf("User Task #%u send = %u \n", task_id, p);
	shared_value = p;

	kernel_yield();

	delay(1000);

	debug_printf("User Task #%u shared value = %u \n", task_id, shared_value);

	kernel_unlock_mutex();

	// kernel_unlock_sem();
}
