#include "GPIO.h"

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
