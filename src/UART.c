#include "UART.h"

#include <stdarg.h>
#include <stdio.h>

void
UART_PutC(char c)
{
	dmb();
	
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

	UART_PutNewline();
}

void
UART_PutB(char *str, u32 size)
{
	while (size--)
	{
		UART_PutC(*str++);
	}
}

void
UART_Printf(const char *fmt, ...)
{
	char buffer[2048];

	va_list args;
	va_start(args, fmt);

	vsprintf(buffer, fmt, args);

	UART_Puts(buffer);

	va_end(args);
}

char
UART_GetC(void)
{
	while (!(*AUX_MU_LSR & _AUX_ME_LSR_DATA_READY_MASK))
	{
		nop();
	}

	return *AUX_MU_IO;
}

u32
UART_GetS(char *str)
{
	u32 count = 1;
	char c;

	bool done = false;

	while (!done)
	{
		c = UART_GetC();

		if (c != '\r')
		{
			*str++ = c;
			++count;
			UART_PutC(c);
		}
		else
		{
			done = true;
			UART_PutNewline();
		}
	}

	*str = '\0';

	return count;
}

void
UART_Flush(void)
{
	while(!(*AUX_MU_LSR & _AUX_ME_LSR_TRANS_IDLE_MASK))
	{
		nop();
	}
}
