#include "GPIO.h"

#define UNUSED(a) (void) a

void
exit(u32 code)
{
    UNUSED(code);

    for(;;) {}
}

void 
main(void)
{
    SetGPIOMode(GPIO_LED, GPIO_OUTPUT);
    SetGPIOMode(GPIO_2, GPIO_INPUT);

    while (1)
    {
        bool shouldLight = !(*GPLEV0 & (1 << GPIO_2));

        if (shouldLight)
        {
            ClearGPIO(GPIO_LED);
        }
        else
        {
            SetGPIO(GPIO_LED);
        }
    }

    exit(0);
}
