#include "stdint.h"
#include "stdbool.h"

#include "ARMv7AR.h"
#include "armcpu.h"
#include "task.h"

static kernel_tcb_t task_list[MAX_TASK_NUM];

static kernel_tcb_t *current_tcb;
static kernel_tcb_t *next_tcb;

static uint32_t		allocated_tcb_index;
static uint32_t		current_tcb_index;

static kernel_tcb_t *scheduler_round_robin_algorithm(void);

static void save_context(void);
static void restore_context(void);

void kernel_task_init(void)
{
	allocated_tcb_index = 0;
	current_tcb_index = 0;

	for (uint32_t i = 0; i < MAX_TASK_NUM; i++)
	{
		task_list[i].stack_base = (uint8_t *)(
			TASK_STACK_START + 
			(i * USR_TASK_STACK_SIZE)
		);

		task_list[i].sp = (uint32_t)(
			task_list[i].stack_base +
			USR_TASK_STACK_SIZE - 4
		);

		task_list[i].sp -= sizeof(kernel_task_context_t);
		
		kernel_task_context_t *ctx = (kernel_task_context_t *)task_list[i].sp;
		ctx->pc = 0;
		ctx->spsr = ARM_MODE_BIT_SYS;
	}
}

void kernel_task_start(void)
{
	next_tcb = &task_list[current_tcb_index];
	restore_context();
}

uint32_t kernel_task_create(kernel_task_func_t start_func)
{
	kernel_tcb_t *new_tcb = &task_list[allocated_tcb_index++];

	if (allocated_tcb_index > MAX_TASK_NUM)
		return NOT_ENOUGH_TASK_NUM;

	kernel_task_context_t *ctx = (kernel_task_context_t *)new_tcb->sp;
	ctx->pc = (uint32_t)start_func;

	return (allocated_tcb_index - 1);
}

void kernel_task_scheduler(void)
{
	current_tcb = &task_list[current_tcb_index];
	next_tcb = scheduler_round_robin_algorithm();

	disable_irq();
	kernel_task_context_switching();
	enable_irq();
}

__attribute__ ((naked)) void kernel_task_context_switching(void)
{
	__asm__ ("B save_context");
	__asm__ ("B restore_context");
}

static __attribute__ ((naked)) void save_context(void)
{
	// save current task context into the current task stack
	__asm__ ("PUSH {lr}");
	__asm__ ("PUSH {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("MRS	r0, cpsr");
	__asm__ ("PUSH {r0}");

	// save current task tsack pointer into the current TCB
	__asm__ ("LDR	r0, =current_tcb");
	__asm__ ("LDR	r0, [r0]");
	__asm__ ("STMIA r0!, {sp}");
}

static __attribute__ ((naked)) void restore_context(void)
{
	// restore next task stack pointer from the next TCB
	__asm__ ("LDR	r0, =next_tcb");
	__asm__ ("LDR	r0, [r0]");
	__asm__ ("LDMIA r0!, {sp}");

	// restore next task context from the next task stack
	__asm__ ("POP	{r0}");
	__asm__ ("MSR	cpsr, r0");
	__asm__ ("POP	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("POP	{pc}");
}

static kernel_tcb_t *scheduler_round_robin_algorithm(void)
{
	current_tcb_index++;
	current_tcb_index %= allocated_tcb_index;

	return &task_list[current_tcb_index];
}

