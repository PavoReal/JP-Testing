/**
 * \file Arm.h
 * \brief Register and system definitions for the BCM2835
 * 
 * *Example Projects*:
 *
 * [xinu](https://embedded-xinu.readthedocs.io/en/latest/index.html)
 *
 * Based on the following docs:
 *
 * [https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)
 *
 * [http://elinux.org/RPi_Low-level_peripherals](http://elinux.org/RPi_Low-level_peripherals) 
 *
 * [http://www.scribd.com/doc/101830961/GPIO-Pads-Control2](http://www.scribd.com/doc/101830961/GPIO-Pads-Control2)
 *
 */
#if !defined(JP_ARM_H)
#define JP_ARM_H


// We don't want the compiler  bitching about every unused variable here
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdint.h>
#include <stdbool.h>

///
/// \addtogroup Common
/// @{
///

/// 8 bit signed int
typedef int8_t s8;

/// 16 bit signed int
typedef int16_t s16;

/// 32 bit signed int
typedef int32_t s32;

/// 64 bit signed int
typedef int64_t s64;

/// 8 bit unsigned int
typedef uint8_t u8;

/// 16 bit unsigned int
typedef uint16_t u16;

/// 32 bit unsigned int
typedef uint32_t u32;

/// 64 bit unsigned int
typedef uint64_t u64;

typedef unsigned int uint;

/// @}

///\addtogroup Common
///@{

/** \brief Use between different peripheral read / writes
 *  
 * From page 7 of the ARM Peripheral datasheet:
 * Accesses  to  the  same  peripheral  will  always  arrive  and  return  in-order.    It  is  only  when switching from
 * one peripheral to another that data can arrive out-of-order. The simplest way to make sure that data is processed
 * in-order is to place a memory barrier instruction at critical positions in the code. You should place: •A memory 
 * write barrier before the first write to a peripheral. •A memory read barrier after the last read of a peripheral. It 
 * is not required to put a memory barrier instruction after each read or write access. Only at those places  in the 
 * code where  it  is possible that a peripheral read or write  may  be  followed by a read or write of a different 
 * peripheral. This is normally at the entry and exit points of the peripheral service code. 
 */
extern void
dmb(void);

/** \brief nop
 *
 * Will just \c bx \c to the link register (\c lr \c)
 */
extern void 
nop();

/// @}
/// \addtogroup Peripherals
/// @{

/// The start of physical peripheral memory
#define PERIPHERAL_BASE_ADDR (0x20000000)

/// The end of physical physical memory \note(Peacock): This needs to be verified
#define PERIPHERAL_MAX_ADDR (0x20FFFFFF)

/// \addtogroup Auxilliary
/// @{

/// Auxiliary Interrupt Status, 3 bits \note(Peacock): This needs to be verified
#define AUX_IRQ_ADDR (0x20215000)

/// Auxiliary Enables, 3 bits \note(Peacock): This needs to be verified
#define AUX_ENABLES_ADDR (0x20215004)

/// \addtogroup UART
/// @{
/// Mini Uart I/O Data, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_IO_REG_ADDR (0x20215040)

/// Mini Uart Interrupt Enable, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_IER_ADDR (0x20215044)

/// Mini Uart Interrupt Identify, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_IIR_ADDR (0x20215048)

/// Mini Uart Line Control, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_LCR_ADDR (0x2021504C)

/// Mini Uart Modem Control, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_MCR_ADDR (0x20215050)

/// Mini Uart Line Status, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_LSR_ADDR (0x20215054)

/// Mini Uart Modem Status, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_MSR_ADDR (0x20215058)

/// Mini Uart Scratch, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_SCRATCH_ADDR (0x2021505C)

/// Mini Uart Extra Control, 8 bits \note(Peacock): This needs to be verified
#define AUX_MU_CNTL_ADDR (0x20215060)

/// Mini Uart Extra Status, 32 bits \note(Peacock): This needs to be verified
#define AUX_MU_STAT_ADDR (0x20215064)

/// Mini Uart Baudrate, 16 bits \note(Peacock): This needs to be verified
#define AUX_MU_BAUD_ADDR  (0x20215068)

/// @}
/// \addtogroup SPI
/// @{

/// SPI 1 Control register 0, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI0_CNTL0_ADDR (0x20215080)

/// SPI 1 Control register 1, 8 bits \note(Peacock): This needs to be verified
#define AUX_SPI0_CNTL1_ADDR (0x20215084)

/// SPI1 Status, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI0_STAT_ADDR (0x20215088)

/// SPI1 Data, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI0_IO_ADDR (0x20215090)

/// SPI1 Peek, 16 bits \note(Peacock): This needs to be verified
#define AUX_SPI0_PEEK_ADDR (0x20215094)

/// SPI2 Control register 0, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI1_CNTL0_ADDR (0x202150C0)

/// SPI2 Control register 1, 8 bits \note(Peacock): This needs to be verified
#define AUX_SPI1_CNTL1_ADDR (0x202150C4)

/// SPI2 Status, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI1_STAT_ADDR (0x202150C8)

/// SPI2 Data, 32 bits \note(Peacock): This needs to be verified
#define AUX_SPI1_IO_ADDR (0x202150D0)

/// SPI2 Peek, 16 bits \note(Peacock): This needs to be verified
#define AUX_SPI1_PEEK_ADDR (0x202150D4)

/// @}
/// @}

/**
 * \addtogroup GPIO 
 * The function select registers are used to define the operation of the general-purpose I/O pins. Each of the 54 GPIO 
 * pins has at least two alternative functions as defined in section 16.2. The FSEL{n} field determines the
 * functionality of the nth GPIO pin. All unused alternative function lines are tied to ground and will output a “0” if
 * selected. All pins reset to normal GPIO input operation.
 * @{
 */

/// GPIO Function Select 0, 32 bits, R/W
#define FSEL0_ADDR (0x20200000) 

/// GPIO Function Select 1, 32 bits, R/W
#define FSEL1_ADDR (0x20200004) 

/// GPIO Function Select 2, 32 bits, R/W
#define FSEL2_ADDR (0x20200008) 

/// GPIO Function Select 3, 32 bits, R/W
#define FSEL3_ADDR (0x2020000C) 

/// GPIO Function Select 4, 32 bits, R/W
#define FSEL4_ADDR (0x20200010) 

/// GPIO Function Select 5, 32 bits, R/W
#define FSEL5_ADDR (0x20200014) 

static volatile u32 * const FSEL0 = (u32*) FSEL0_ADDR;
static volatile u32 * const FSEL1 = (u32*) FSEL1_ADDR;
static volatile u32 * const FSEL2 = (u32*) FSEL2_ADDR;
static volatile u32 * const FSEL3 = (u32*) FSEL3_ADDR;
static volatile u32 * const FSEL4 = (u32*) FSEL4_ADDR;
static volatile u32 * const FSEL5 = (u32*) FSEL5_ADDR;

/// GPIO Pin Output Set 0, 32 bits, W only
#define SET0_ADDR  (0x2020001C) 

/// GPIO Pin Output Set 1, 32 bits, W only
#define SET1_ADDR  (0x20200020) 

static volatile u32 * const SET0 = (u32*) SET0_ADDR;
static volatile u32 * const SET1 = (u32*) SET1_ADDR;

/// GPIO Pin Output Clear 0, 32 bits, W only
#define CLR0_ADDR  (0x20200028) 

/// GPIO Pin Output Clear 1, 32 bits, W only
#define CLR1_ADDR  (0x2020002C) 

static volatile u32 * const CLR0 = (u32*) CLR0_ADDR;
static volatile u32 * const CLR1 = (u32*) CLR1_ADDR;

/// GPIO Pin Level 0, 32 bits, R only
#define LEV0_ADDR  (0x20200034) 

/// GPIO Pin Level 1, 32 bits, R only
#define LEV1_ADDR  (0x20200038) 

static volatile u32 * const LEV0 = (u32*) LEV0_ADDR;
static volatile u32 * const LEV1 = (u32*) LEV1_ADDR;

/// GPIO Pin 47 Mask For \c SET1 \c
#define _SET1_P47_MASK (1 << (47 - 32))

/// GPIO LED Mask For \c SET1 \c. (Tied to Pin 47)
#define _SET1_LED_MASK (_SET1_P47_MASK)

/// GPIO Pin 47 Mask For \c CLR1 \c
#define _CLR1_P47_MASK (1 << (47 - 32))
/// GPIO LED Mask For \c CLR1 \c. (Tied to Pin 47)
#define _CLR1_LED_MASK (_CLR1_P47_MASK) 

/// @}

///
/// \addtogroup SYSTIMER
///
/// System Timer is a memory-mapped peripheral. It features a 64-bit free-running counter that runs at 1
/// MHz and four separate “output compare registers” that can be used to schedule interrupts. However, two output 
/// compare registers are already used by the VideoCore GPU, leaving only two available for the ARM CPU to use.
/// @{
///

/// \note(Peacock): This needs to be verified
#define SYSTIMER_FREQ (1000000)

/// System Timer Control / Status, 32 bits
#define SYSTIMER_CS_ADDR (0x20003000) 

/// System Timer Counter Lower 32 bits
#define SYSTIMER_CLO_ADDR (0x20003004) 

/// System Timer Counter Higher 32 bits
#define SYSTIMER_CHI_ADDR (0x20003008) 

/// \brief System Timer Compare 0
/// \note(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_C0_ADDR (0x2000300C)

/// System Timer Compare 1
#define SYSTIMER_C1_ADDR (0x20003010)

/// \brief System Timer Compare 2
/// \note(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_C2_ADDR (0x20003014)

/// System Timer Compare 3
#define SYSTIMER_C3_ADDR (0x20003018)

/// \brief System Timer Match 0, IRQ line 0
/// \note(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_CS_M0_MASK (1 << 0) 

/// System Timer Match 1, IRQ line 1
#define SYSTIMER_CS_M1_MASK (1 << 1)

/// \brief System Timer Match 2, IRQ line 2
/// \note(Peacock): Reserved by GPU -- DO NOT USE
#define SYSTIMER_CS_M2_MASK (1 << 2) // System Timer Match 2, IRQ line 2

/// System Timer Match 3, IRQ line 3
#define SYSTIMER_CS_M3_MASK (1 << 3) 

static volatile u32 * const SYSTIMER_CS       = (u32*) SYSTIMER_CS_ADDR;
static volatile u32 * const SYSTIMER_CLO      = (u32*) SYSTIMER_CLO_ADDR;
static volatile u32 * const SYSTIMER_CHI      = (u32*) SYSTIMER_CHI_ADDR;
static volatile const u32 * const SYSTIMER_C0 = (u32*) SYSTIMER_C0_ADDR;
static volatile u32 * const SYSTIMER_C1       = (u32*) SYSTIMER_C1_ADDR;
static volatile const u32 * const SYSTIMER_C2 = (u32*) SYSTIMER_C2_ADDR;
static volatile u32 * const SYSTIMER_C3       = (u32*) SYSTIMER_C3_ADDR;

/// @}

///
/// \addtogroup IRQ
///

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

///@}

#endif
