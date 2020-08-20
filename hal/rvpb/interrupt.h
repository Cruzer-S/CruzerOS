#ifndef HAL_RVPB_INTERRUPT_H_
#define HAL_RVPB_INTERRUPT_H_

typedef union cpu_control_t
{
    uint32_t all;
    struct {
        uint32_t enable:1;          // 0
        uint32_t reserved:31;
    } bits;
} cpu_control_t;

typedef union priority_mask_t
{
    uint32_t all;
    struct {
        uint32_t reserved_1:4;        // 3:0
        uint32_t priority_mask:4;    // 7:4
        uint32_t reserved_2:24;
    } bits;
} priority_mask_t;

typedef union binary_point_t
{
    uint32_t all;
    struct {
        uint32_t binary_point:3;     // 2:0
        uint32_t reserved:29;
    } bits;
} binary_point_t;

typedef union interrupt_ack_t
{
    uint32_t all;
    struct {
        uint32_t interrupt_id:10;    // 9:0
        uint32_t cpu_source_iD:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} interrupt_ack_t;

typedef union end_of_interrupt_t
{
    uint32_t all;
    struct {
        uint32_t interrupt_id:10;    // 9:0
        uint32_t cpu_source_id:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} end_of_interrupt_t;

typedef union running_interrupt_t
{
    uint32_t all;
    struct {
        uint32_t reserved_1:4;        // 3:0
        uint32_t priority:4;        // 7:4
        uint32_t reserved_2:24;
    } bits;
} running_interrupt_t;

typedef union highest_pend_inter_t
{
    uint32_t all;
    struct {
        uint32_t interrupt_id:10;    // 9:0
        uint32_t cpu_source_id:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} highest_pend_inter_t;

typedef union distributor_ctrl_t
{
    uint32_t all;
    struct {
        uint32_t enable:1;          // 0
        uint32_t reserved:31;
    } bits;
} distributor_ctrl_t;

typedef union controller_type_t
{
    uint32_t all;
    struct {
        uint32_t id_linesnumber:5;   // 4:0
        uint32_t cpu_number:3;       // 7:5
        uint32_t reserved:24;
    } bits;
} controller_type_t;

typedef struct gic_cput_t
{
    cpu_control_t			cpu_control;        //0x000
    priority_mask_t			priority_mask;      //0x004
    binary_point_t			binary_point;       //0x008
    interrupt_ack_t			interrupt_ack;      //0x00C
    end_of_interrupt_t		end_of_interrupt;    //0x010
    running_interrupt_t		running_interrupt;  //0x014
    highest_pend_inter_t	highest_pend_inter;  //0x018
} gic_cput_t;

typedef struct gic_dist_t
{
    distributor_ctrl_t	distributor_ctrl;    //0x000
    controller_type_t	controller_type;     //0x004
    uint32_t            reserved0[62];      //0x008-0x0FC
    uint32_t            reserved1;          //0x100
    uint32_t            set_enable1;         //0x104
    uint32_t            set_enable2;         //0x108
    uint32_t            reserved2[29];      //0x10C-0x17C
    uint32_t            reserved3;          //0x180
    uint32_t            clear_enable1;       //0x184
    uint32_t            clear_enable2;       //0x188
} gic_dist_t;

#define GIC_CPU_BASE  0x1E000000  //CPU interface
#define GIC_DIST_BASE 0x1E001000  //distributor

#define GIC_PRIORITY_MASK_NONE  0xF

#define GIC_IRQ_START           32
#define GIC_IRQ_END             95

#endif /* HAL_RVPB_INTERRUPT_H_ */
