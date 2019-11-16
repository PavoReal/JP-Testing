#include "GPIO.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(a) (void) a

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
    {}
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
    SetGPIOMode(GPIO_15, GPIO_ALT5);
}

void
StartUART(void)
{   
    dmb();
    *AUX_MU_CNTL = 3;
}

int 
start(void)
{
    SetupUART();
    StartUART();

    UART_Puts("Hello JP!");
    char c = UART_GetC();
    
    UART_PutC(c);
    UART_Puts("");

    while (1)
    {
        char buffer[1024];
        UART_GetS(buffer);

        UART_Puts(buffer);
    }

    return EXIT_SUCCESS;
}
