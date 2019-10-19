#if !defined(JP_GPIO_H)
#define JP_GPIO_H

#include "BCM2835.h"

#define GPIO_0 (0)
#define GPIO_1 (1)
#define GPIO_2 (2)
#define GPIO_3 (3)
#define GPIO_4 (4)
#define GPIO_5 (5)
#define GPIO_6 (6)
#define GPIO_7 (7)
#define GPIO_8 (8)
#define GPIO_9 (9)
#define GPIO_10 (10)
#define GPIO_11 (11)
#define GPIO_12 (12)
#define GPIO_13 (13)
#define GPIO_14 (14)
#define GPIO_15 (15)
#define GPIO_16 (16)
#define GPIO_17 (17)
#define GPIO_18 (18)
#define GPIO_19 (19)
#define GPIO_20 (20)
#define GPIO_21 (21)
#define GPIO_22 (22)
#define GPIO_23 (23)
#define GPIO_24 (24)
#define GPIO_25 (25)
#define GPIO_26 (26)
#define GPIO_27 (27)
#define GPIO_28 (28)
#define GPIO_29 (29)
#define GPIO_30 (30)
#define GPIO_31 (31)
#define GPIO_32 (32)
#define GPIO_33 (33)
#define GPIO_34 (34)
#define GPIO_35 (35)
#define GPIO_36 (36)
#define GPIO_37 (37)
#define GPIO_38 (38)
#define GPIO_39 (39)
#define GPIO_40 (40)
#define GPIO_41 (41)
#define GPIO_42 (42)
#define GPIO_43 (43)
#define GPIO_44 (44)
#define GPIO_45 (45)
#define GPIO_46 (46)
#define GPIO_47 (47)
#define GPIO_48 (48)
#define GPIO_49 (49)
#define GPIO_50 (50)
#define GPIO_51 (51)
#define GPIO_52 (52)
#define GPIO_53 (53)

#define GPIO_LED GPIO_47

#define GPIO_OUTPUT GPIO_PIN_OUTPUT
#define GPIO_INPUT GPIO_PIN_INPUT

void
SetGPIOMode(u32 pin, u32 mode)
{
    if (pin <= 9)
    {
        // GPFSEL0
        // Get the bit position we need to change
        pin = (pin - 0) * 3;

        // Zero out the target bits
        *GPFSEL0 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL0 |= mode << pin;
    }
    else if (pin <= 19)
    {
        // GPFSEL1
        // Get the bit position we need to change
        pin = (pin - 10) * 3;

        // Zero out the target bits
        *GPFSEL1 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL1 |= mode << pin;
    }
    else if (pin <= 29)
    {
        // GPFSEL2
        // Get the bit position we need to change
        pin = (pin - 20) * 3;

        // Zero out the target bits
        *GPFSEL2 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL2 |= mode << pin;
    }
    else if (pin <= 39)
    {
        // GPFSEL3
        // Get the bit position we need to change
        pin = (pin - 30) * 3;

        // Zero out the target bits
        *GPFSEL3 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL3 |= mode << pin;
    }
    else if (pin <= 49)
    {
        // GPFSEL4
        // Get the bit position we need to change
        pin = (pin - 40) * 3;

        // Zero out the target bits
        *GPFSEL4 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL4 |= mode << pin;
    }
    else
    {
        // GPFSEL5
        // Get the bit position we need to change
        pin = (pin - 50) * 3;

        // Zero out the target bits
        *GPFSEL5 &= ~(7 << pin);
        // Update the target bits
        *GPFSEL5 |= mode << pin;
    }
}

//
// NOTE(Peacock): For some reason the GPSETx and GPCLRx registers seem to be reversed...
//
void
SetGPIO(u32 pin)
{
    if (pin <= 31)
    {
        *GPSET0 = (1 << pin);
    }
    else
    {
        pin -= 32;
       *GPSET1 = (1 << pin);
    }
}

void
ClearGPIO(u32 pin)
{
    if (pin <= 31)
    {
        *GPCLR0 = (1 << pin);
    }
    else
    {
        pin -= 32;
       *GPCLR1 = (1 << pin);
    }
}


#endif
