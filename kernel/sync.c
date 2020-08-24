#include "sync.h"

static int32_t sem_max;
static int32_t sem;
static kernel_mutex_t mutex;

void kernel_sem_init(int32_t max)
{
	sem_max = (max <= 0) ? DEF_SEM_MAX : max;

	sem_max = (max >= DEF_SEM_MAX) ? DEF_SEM_MAX : max;

	sem = sem_max;
}

bool kernel_sem_test(void)
{
	if (sem <= 0)
		return false;

	sem--;

	return true;
}

void kernel_sem_release(void)
{
	sem++;

	if (sem >= sem_max)
		sem = sem_max;
}

void kernel_mutex_init(void)
{
	mutex.owner = 0;
	mutex.lock = false;
}

bool kernel_mutex_lock(uint32_t owner)
{
	if (mutex.lock)
		return false;

	mutex.owner = owner;
	mutex.lock = true;

	return true;
}

bool kernel_mutex_unlock(uint32_t owner)
{
	if (owner == mutex.owner)
	{
		mutex.lock = false;
		return true;
	}

	return false;
}
