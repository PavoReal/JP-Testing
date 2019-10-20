#include "UART.h"

void
UART_PutC(char c)
{
	while (1)
    {
    	if (*AUX_MU_LSR & _AUX_MU_LSR_TRANS_EMPTY_MASK)
    	{
    		break;
    	}
    }

    *AUX_MU_IO = c;
}

void
UART_Puts(char *str)
{
	while (*str)
	{
		UART_PutC(*str++);
	}
	UART_PutC('\r');
	UART_PutC('\n');
}

void
UART_PutB(char *str, u32 size)
{
	while (size--)
	{
		UART_PutC(*str++);
	}
}