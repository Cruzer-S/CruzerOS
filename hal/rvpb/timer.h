#ifndef HAL_RVPB_TIMER_H_
#define HAL_RVPB_TIMER_H_

typedef union timer_control_t
{
    uint32_t all;
    struct {
        uint32_t one_shot:1;     //0
        uint32_t timer_size:1;   //1
        uint32_t timer_pre:2;    //3:2
        uint32_t reserved_0:1;   //4
        uint32_t int_enable:1;   //5
        uint32_t timer_mode:1;   //6
        uint32_t timer_en:1;     //7
        uint32_t reserved_1:24;  //31:8
    } bits;
} timer_control_t;

typedef union timer_ris_t
{
    uint32_t all;
    struct {
        uint32_t timer_ris:1;   //0
        uint32_t reserved:31;   //31:1
    } bits;
} timer_ris_t;

typedef union timer_mis_t
{
    uint32_t all;
    struct {
        uint32_t timer_mis:1;   //0
        uint32_t reserved:31;   //31:1
    } bits;
} timer_mis_t;

typedef struct timer_t
{
    uint32_t        timer_load;     // 0x00
    uint32_t        timer_value;    // 0x04
    timer_control_t timer_control;  // 0x08
    uint32_t        timer_int_clr;   // 0x0C
    timer_ris_t     timer_ris;      // 0x10
    timer_mis_t     timer_mis;      // 0x14
    uint32_t        timer_bg_load;   // 0x18
} timer_t;

#define TIMER_CPU_BASE  0x10011000
#define TIMER_INTERRUPT 36

#define TIMER_FREERUNNING   0
#define TIMER_PERIOIC       1

#define TIMER_16BIT_COUNTER 0
#define TIMER_32BIT_COUNTER 1

#define TIMER_10HZ_INTERVAL       (32768 * 4)

#endif /* HAL_RVPB_TIMER_H_ */
