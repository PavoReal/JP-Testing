#include "Arm.h"

int 
main(void)
{
    dmb();
    // Enable IRQ line 1, which is our systimer timer compare register 1
    *IRQ_ENABLE_IRQ_1 = (*IRQ_ENABLE_IRQ_1 | (IRQ_PENDING_1_C1_MASK));

    dmb();

    // Set only the led pin to an output
    *GP_FSEL4 &= ~(7 << 21);
    *GP_FSEL4 |= (1 << 21);
    *GP_CLR1 = GP_CLR1_LED_MASK;

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
                *GP_CLR1 = GP_CLR1_LED_MASK;
                dmb();
            }
            else
            {
                dmb();
                *GP_SET1 = GP_SET1_LED_MASK;
                dmb();
            }

            even = !even;
        }
    }

    return 0;
}
