#include "stdint.h"
#include "uart.h"
#include "interrupt.h"

volatile PL011_t*	uart		= (PL011_t*)UART_BASE_ADDRESS0;
volatile gic_cput_t *gic_cpu	= (gic_cput_t *)GIC_CPU_BASE;
volatile gic_dist_t *gic_dist	= (gic_dist_t *)GIC_DIST_BASE;
