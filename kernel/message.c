#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#include "memio.h"

#include "message.h"

kernel_circular_t message_queue[kernel_message_num];

void kernel_message_init(void)
{
	for (uint32_t i = 0; i < kernel_message_num; i++)
	{
		message_queue[i].front = 0;
		message_queue[i].rear = 0;

		memclr(message_queue[i].queue, MSG_Q_SIZE_BYTE);
	}
}

bool kernel_message_is_empty(kernel_message_t name)
{
	if (name >= kernel_message_num)
		return false;

	if (message_queue[name].front == message_queue[name].rear)
		return true;

	return false;
}

bool kernel_message_is_full(kernel_message_t name)
{
	if (name >= kernel_message_num)
		return false;

	if (((message_queue[name].rear + 1) % MSG_Q_SIZE_BYTE) == message_queue[name].front)
		return true;

	return false;
}

bool kernel_message_enqueue(kernel_message_t name, uint8_t data)
{
	if (name >= kernel_message_num)
		return false;

	if (kernel_message_is_full(name))
		return false;

	message_queue[name].rear++;
	message_queue[name].rear %= MSG_Q_SIZE_BYTE;

	uint32_t index = message_queue[name].rear;
	message_queue[name].queue[index] = data;

	return true;
}

bool kernel_message_dequeue(kernel_message_t name, uint8_t *out_data)
{
	if (name >= kernel_message_num)
		return false;

	if (kernel_message_is_empty(name))
		return false;

	message_queue[name].front++;
	message_queue[name].front %= MSG_Q_SIZE_BYTE;

	uint32_t index = message_queue[name].front;
	*out_data = message_queue[name].queue[index];

	return true;
}
