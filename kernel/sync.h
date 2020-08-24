#ifndef _KERNEL_SYNC_H_
#define _KERNEL_SYNC_H_

#include "stdint.h"
#include "stdbool.h"

typedef struct kernel_mutex_t
{
	uint32_t owner;
	bool lock;
} kernel_mutex_t ;

#define DEF_SEM_MAX 8

void kernel_sem_init(int32_t max);
bool kernel_sem_test(void);
void kernel_sem_release(void);

void kernel_mutex_init(void);
bool kernel_mutex_lock(uint32_t owner);
bool kernel_mutex_unlock(uint32_t owner);

#endif
