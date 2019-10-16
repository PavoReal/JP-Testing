#if !defined(JP_ARM_H)
#define JP_ARM_H

//
// Some docs @:
// https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
// https://embedded-xinu.readthedocs.io/en/latest/index.html
//

#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdint.h>
#include <stdbool.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef unsigned int uint;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/** From page 7 of the ARM Peripheral datasheet:
Accesses  to  the  same  peripheral  will  always  arrive  and  return  in-order.    It  is  only  when switching from
one peripheral to another that data can arrive out-of-order. The simplest way to make sure that data is processed
in-order is to place a memory barrier instruction at critical positions in the code. You should place: •A memory 
write barrier before the first write to a peripheral. •A memory read barrier after the last read of a peripheral. It 
is not required to put a memory barrier instruction after each read or write access. Only at those places  in the 
code where  it  is possible that a peripheral read or write  may  be  followed by a read or write of a different 
peripheral. This is normally at the entry and exit points of the peripheral service code. 
**/
extern void
dmb(void);

extern void 
nop();

//
// GPIO Registers
//

// NOTE(Peacock): The datasheet (https://www.raspberrypi.org/documentation/hardware/raspberrypi/
// bcm2835/BCM2835-ARM-Peripherals.pdf) uses a base address of 0x7E20xxxx for these. That is from the GPUs
// perspective, 0x2020xxxx is for our ARM core

#define GP_FSEL0_ADDR (0x20200000) // GPIO Function Select 0, 32 bits, R/W
#define GP_FSEL1_ADDR (0x20200004) // GPIO Function Select 1, 32 bits, R/W
#define GP_FSEL2_ADDR (0x20200008) // GPIO Function Select 2, 32 bits, R/W
#define GP_FSEL3_ADDR (0x2020000C) // GPIO Function Select 3, 32 bits, R/W
#define GP_FSEL4_ADDR (0x20200010) // GPIO Function Select 4, 32 bits, R/W
#define GP_FSEL5_ADDR (0x20200014) // GPIO Function Select 5, 32 bits, R/W
static volatile u32 * const GP_FSEL0 = (u32*) GP_FSEL0_ADDR;
static volatile u32 * const GP_FSEL1 = (u32*) GP_FSEL1_ADDR;
static volatile u32 * const GP_FSEL2 = (u32*) GP_FSEL2_ADDR;
static volatile u32 * const GP_FSEL3 = (u32*) GP_FSEL3_ADDR;
static volatile u32 * const GP_FSEL4 = (u32*) GP_FSEL4_ADDR;
static volatile u32 * const GP_FSEL5 = (u32*) GP_FSEL5_ADDR;

#define GP_SET0_ADDR  (0x2020001C) // GPIO Pin Output Set 0, 32 bits, W
#define GP_SET1_ADDR  (0x20200020) // GPIO Pin Output Set 1, 32 bits, W
static volatile u32 * const GP_SET0 = (u32*) GP_SET0_ADDR;
static volatile u32 * const GP_SET1 = (u32*) GP_SET1_ADDR;

#define GP_CLR0_ADDR  (0x20200028) // GPIO Pin Output Clear 0, 32 bits, w
#define GP_CLR1_ADDR  (0x2020002C) // GPIO Pin Output Clear 1, 32 bits, w
static volatile u32 * const GP_CLR0 = (u32*) GP_CLR0_ADDR;
static volatile u32 * const GP_CLR1 = (u32*) GP_CLR1_ADDR;

#define GP_LEV0_ADDR  (0x20200034) // GPIO Pin Level 0, 32 bits, R
#define GP_LEV1_ADDR  (0x20200038) // GPIO Pin Level 1, 32 bits, R
static volatile u32 * const GP_LEV0 = (u32*) GP_LEV0_ADDR;
static volatile u32 * const GP_LEV1 = (u32*) GP_LEV1_ADDR;

//
// GPIO Pins
//

#define GP_SET1_P47_MASK (1 << (47 - 32))
#define GP_SET1_LED_MASK (GP_SET1_P47_MASK)

#define GP_CLR1_P47_MASK (1 << (47 - 32))
#define GP_CLR1_LED_MASK (GP_CLR1_P47_MASK) 

//
// System Timer Registers
//
// NOTE(Peacock): System Timer is a memory-mapped peripheral. It features a 64-bit free-running counter that runs at 1
// MHz and four separate “output compare registers” that can be used to schedule interrupts. However, two output 
// compare registers are already used by the VideoCore GPU, leaving only two available for the ARM CPU to use.
//

#define SYSTIMER_FREQ (1000000)

#define SYSTIMER_CS_ADDR (0x20003004) // System Timer Control / Status
#define SYSTIMER_CLO_ADDR (0x20003004) // System Timer Counter Lower 32 bits
#define SYSTIMER_CHI_ADDR (0x20003008) // System Timer Counter Higher 32 bits
// NOTE(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_C0_ADDR (0x2000300C)
#define SYSTIMER_C1_ADDR (0x20003010)
// NOTE(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_C2_ADDR (0x20003014)
#define SYSTIMER_C3_ADDR (0x20003018)

// NOTE(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_CS_M0_MASK (1 << 0) // System Timer Match 0, IRQ line 0
#define SYSTIMER_CS_M1_MASK (1 << 1) // System Timer Match 1, IRQ line 1
// NOTE(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_CS_M2_MASK (1 << 2) // System Timer Match 2, IRQ line 2
#define SYSTIMER_CS_M3_MASK (1 << 3) // System Timer Match 3, IRQ line 3

static volatile u32 * const SYSTIMER_CS       = (u32*) SYSTIMER_CS_ADDR;
static volatile u32 * const SYSTIMER_CLO      = (u32*) SYSTIMER_CLO_ADDR;
static volatile u32 * const SYSTIMER_CHI      = (u32*) SYSTIMER_CHI_ADDR;
static volatile const u32 * const SYSTIMER_C0 = (u32*) SYSTIMER_C0_ADDR;
static volatile u32 * const SYSTIMER_C1       = (u32*) SYSTIMER_C1_ADDR;
static volatile const u32 * const SYSTIMER_C2 = (u32*) SYSTIMER_C2_ADDR;
static volatile u32 * const SYSTIMER_C3       = (u32*) SYSTIMER_C3_ADDR;

//
// IRQ Registers
//

#define IRQ_BASIC_PENDING_ADDR (0x2000B200) // Pending ARM specific IRQs status, with additional info
#define IRQ_PENDING_1_ADDR     (0x2000B204) // Pending shared IRQs status 1
#define IRQ_PENDING_2_ADDR     (0x2000B208) // Pending shared IRQs status 2
#define IRQ_FIQ_CONTROL_ADDR   (0x2000B20C)
#define IRQ_ENABLE_IRQ_1_ADDR  (0x2000B210)
#define IRQ_ENABLE_IRQ_2_ADDR  (0x2000B214)
#define IRQ_ENABLE_BASIC_ADDR  (0x2000B218)
#define IRQ_DISABLE_IRQ_1_ADDR (0x2000B21C)
#define IRQ_DISABLE_IRQ_2_ADDR (0x2000B220)
#define IRQ_DISABLE_BASIC_ADDR (0x2000B224)

static volatile u32 * const IRQ_PENDING_1    = (u32*) IRQ_PENDING_1_ADDR;
static volatile u32 * const IRQ_ENABLE_IRQ_1 = (u32*) IRQ_ENABLE_IRQ_1_ADDR;

//
// IRQs
//
#define IRQ_PENDING_1_C1_MASK (1 << 1) // System timer compare 1
#define IRQ_PENDING_1_C3_MASK (1 << 3) // System timer compare 3

#endif
