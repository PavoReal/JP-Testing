#include "Arm.h"



void
TimerIRQHandler(void)
{

}

int 
main(void)
{
    dmb();
    // Enable IRQ line 1, which is our systimer timer compare register 1
    *IRQ_ENABLE_IRQ_1 = (*IRQ_ENABLE_IRQ_1 | (IRQ_PENDING_1_C1_MASK));

    dmb();

    uint w = *FSEL4;

    // Set only the led pin to an output
    w &= ~(7 << 21);
    w |= (1 << 21);

    *FSEL4 = w;

    *CLR1 = _CLR1_LED_MASK;

    dmb();

    // Clear the compare register
    *SYSTIMER_CS = SYSTIMER_CS_M1_MASK;

    // Set our compare register for a two sec freq
    *SYSTIMER_C1 = 2000000; 

    bool even = true;
    while (1)
    {
        if ((*SYSTIMER_CS) & SYSTIMER_CS_M1_MASK)
        {
            *SYSTIMER_CS = SYSTIMER_CS_M1_MASK;

            if (even)
            {
                dmb();
                *CLR1 = _CLR1_LED_MASK;
                dmb();
            }
            else
            {
                dmb();
                *SET1 = _SET1_LED_MASK;
                dmb();
            }

            even = !even;
        }
    }

    return 0;
}
