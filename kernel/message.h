#ifndef KERNEL_MSG_H_
#define KERNEL_MSG_H_

#define MSG_Q_SIZE_BYTE	512

typedef enum kernel_message_t
{
	kernel_message_task_00,
	kernel_message_task_01,
	kernel_message,task_02,

	kernel_message_num
} kernel_message_t;

typedef struct kernel_circular_t
{
	uint32_t front;
	uint32_t rear;

	uint8_t queue[MSG_Q_SIZE_BYTE];
} kernel_circular_t;

void kernel_message_init(void);
bool kernel_message_is_empty(kernel_message_t name);
bool kernel_message_is_full(kernel_message_t name);
bool kernel_message_enqueue(kernel_message_t name, uint8_t data);
bool kernel_message_dequeue(kernel_message_t name, uint8_t *out_data);

#endif
