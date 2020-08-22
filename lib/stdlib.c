#include "stdint.h"
#include "stdbool.h"
#include "hal_timer.h"

void delay(uint32_t ms)
{
	uint32_t goal = hal_timer_get_1ms_counter() + ms;

	while (goal != hal_timer_get_1ms_counter()) ;
}
