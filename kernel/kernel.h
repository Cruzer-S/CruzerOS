#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "task.h"
#include "event.h"
#include "message.h"

void kernel_start(void);
void kernel_yield(void);

void kernel_send_events(uint32_t event_list);
kernel_event_flag_t kernel_wait_events(uint32_t waiting_list);

bool kernel_send_message(kernel_message_t name, void *data, uint32_t count);
uint32_t kernel_receive_message(kernel_message_t name, void *out_data, uint32_t count);

#endif
