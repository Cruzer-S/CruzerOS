/*
 * timer.c
 *
 *  Created on: Sep 27, 2018
 *      Author: yiman
 */

#include "stdint.h"
#include "timer.h"
#include "hal_timer.h"
#include "hal_interrupt.h"

extern volatile timer_t* timer;

static void interrupt_handler(void);

static uint32_t internal_1ms_counter;

void hal_timer_init(void)
{
    // inerface reset
    timer->timer_control.bits.timer_en = 0;
    timer->timer_control.bits.timer_mode = 0;
    timer->timer_control.bits.one_shot = 0;
    timer->timer_control.bits.timer_size = 0;
    timer->timer_control.bits.timer_pre = 0;
    timer->timer_control.bits.int_enable = 1;
    timer->timer_load = 0;
    timer->timer_value = 0xFFFFFFFF;

    // set periodic mode
    timer->timer_control.bits.timer_mode = TIMER_PERIOIC;
    timer->timer_control.bits.timer_size = TIMER_32BIT_COUNTER;
    timer->timer_control.bits.one_shot = 0;
    timer->timer_control.bits.timer_pre = 0;
    timer->timer_control.bits.int_enable = 1;

    uint32_t interval = TIMER_10HZ_INTERVAL / 100;

    timer->timer_load = interval;
    timer->timer_control.bits.timer_en = 1;

    internal_1ms_counter = 0;

    // Register timer interrupt handler
    hal_interrupt_enable(TIMER_INTERRUPT);
    hal_interrupt_register_handler(interrupt_handler, TIMER_INTERRUPT);
}

uint32_t hal_timer_get_1ms_counter(void)
{
    return internal_1ms_counter;
}

static void interrupt_handler(void)
{
    internal_1ms_counter++;

    timer->timer_int_clr = 1;
}
