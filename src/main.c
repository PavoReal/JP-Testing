#include "GPIO.h"
#include "UART.h"
#include <stdio.h>

#define UNUSED(a) (void) a

void
exit(u32 code)
{
    UNUSED(code);

    for(;;) { nop(); }
}

u64
GetSystemTimer(void)
{
    u32 low;
    u32 high;

    dmb();

timerRead:
    low  = *SYSTIMER_CLO;
    high = *SYSTIMER_CHI;

    if (high != *SYSTIMER_CHI)
    {
        goto timerRead;
    }

    u64 result = (high << 31) | low;

    return result;
}

u32
GetSystemTimer32(void)
{
    dmb();

    return *SYSTIMER_CLO;
}

void
DelayS(u32 sec)
{
    u64 target = (sec * SYSTIMER_FREQ) + GetSystemTimer();

    while (target > GetSystemTimer())
    {
        // To nop or not to nop?
        nop();
    }
}

void 
SetupUART(void)
{
    dmb();

    *AUX_ENABLES = _AUX_ENABLES_UART_MASK;
    *AUX_MU_IER  = 0;
    *AUX_MU_CNTL = 0;
    *AUX_MU_LCR  = 3;
    *AUX_MU_MCR  = 0;
    *AUX_MU_IER  = 0;
    *AUX_MU_IIR  = 0xC6;
    *AUX_MU_BAUD = BAUD_DIV_9600;

    dmb();

    SetGPIOMode(GPIO_14, GPIO_ALT5);
}

void 
main(void)
{
    SetupUART();

    dmb();
    SetGPIOMode(GPIO_LED, GPIO_OUTPUT);
    
    dmb();
    *AUX_MU_CNTL = 2;

    u32 number = 0;
    char buffer[512];
    while (1)
    {
        sprintf(buffer, "This shit takes forever #%lu", number++);
        UART_Puts(buffer);
        DelayS(1);
    }

    exit(0);
}
