#ifndef KERNEL_EVENT_H_
#define KERNEL_EVENT_H_

typedef enum kernel_event_flag_t
{
	kernel_event_flag_uart_in		= 0x00000001,
	kernel_event_flag_cmd_in		= 0x00000002,
	kernel_event_flag_cmd_out		= 0x00000004,
	kernel_event_flag_reserved_03	= 0x00000008,
	kernel_event_flag_reserved_04	= 0x00000010,
	kernel_event_flag_reserved_05	= 0x00000020,
	kernel_event_flag_reserved_06	= 0x00000040,
	kernel_event_flag_reserved_07	= 0x00000080,
	kernel_event_flag_reserved_08	= 0x00000100,
	kernel_event_flag_reserved_09	= 0x00000200,
	kernel_event_flag_reserved_10	= 0x00000400,
	kernel_event_flag_reserved_11	= 0x00000800,
	kernel_event_flag_reserved_12	= 0x00001000,	
	kernel_event_flag_reserved_13	= 0x00002000,
	kernel_event_flag_reserved_14	= 0x00004000,
	kernel_event_flag_reserved_15	= 0x00008000,
	kernel_event_flag_reserved_16	= 0x00010000,
	kernel_event_flag_reserved_17	= 0x00020000,
	kernel_event_flag_reserved_18	= 0x00040000,
	kernel_event_flag_reserved_19	= 0x00080000,
	kernel_event_flag_reserved_20	= 0x00100000,
	kernel_event_flag_reserved_21	= 0x00200000,
	kernel_event_flag_reserved_22	= 0x00400000,
	kernel_event_flag_reserved_23	= 0x00800000,
	kernel_event_flag_reserved_24	= 0x01000000,
	kernel_event_flag_reserved_25	= 0x02000000,
	kernel_event_flag_reserved_26	= 0x04000000,
	kernel_event_flag_reserved_27	= 0x08000000,
	kernel_event_flag_reserved_28	= 0x10000000,
	kernel_event_flag_reserved_29	= 0x20000000,
	kernel_event_flag_reserved_30	= 0x40000000,
	kernel_event_flag_reserved_31	= 0x80000000,
	kernel_event_flag_empty			= 0x00000000,
} kernel_event_flag_t;

void kernel_event_flag_init(void);
void kernel_event_flag_set(kernel_event_flag_t event);
void kernel_event_flag_clear(kernel_event_flag_t event);
bool kernel_event_flag_check(kernel_event_flag_t event);

#endif
