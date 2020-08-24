#include "stdint.h"
#include "stdbool.h"
#include "memio.h"

#include "kernel.h"
#include "event.h"

void kernel_start(void)
{
	kernel_task_start();
}

void kernel_yield(void)
{
	kernel_task_scheduler();
}

void kernel_send_events(uint32_t event_list)
{
	for (uint32_t i = 0; i < 32; i++)
	{
		if ((event_list >> i) & 1)
		{
			kernel_event_flag_t sending_event = kernel_event_flag_empty;
			sending_event = (kernel_event_flag_t)SET_BIT(sending_event, i);
			kernel_event_flag_set(sending_event);
		}
	}
}

kernel_event_flag_t kernel_wait_events(uint32_t waiting_list)
{
	for (uint32_t i = 0; i < 32; i++)
	{
		if ((waiting_list >> i) & 1)
		{
			kernel_event_flag_t waiting_event = kernel_event_flag_empty;
			waiting_event = (kernel_event_flag_t)SET_BIT(waiting_event, i);

			if (kernel_event_flag_check(waiting_event))
				return waiting_event;
		}
	}

	return kernel_event_flag_empty;
}

bool kernel_send_message(kernel_message_t name, void *data, uint32_t count)
{
	uint8_t *d = (uint8_t *)data;

	for (uint32_t i = 0; i < count; i++)
	{
		if (kernel_message_enqueue(name, *d) == false)
		{
			for (uint32_t j = 0; j < i; j++)
			{
				uint8_t rollback;
				kernel_message_dequeue(name, &rollback);
			}

			return false;
		}
		d++;
	}

	return true;
}

uint32_t kernel_receive_message(kernel_message_t name, void *out_data, uint32_t count)
{
	uint8_t *d = (uint8_t *)out_data;

	for (uint32_t i = 0; i < count; i++)
	{
		if (kernel_message_dequeue(name, d) == false)
			return i;

		d++;
	}

	return count;
}
