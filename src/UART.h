#if !defined(JP_UART_H)
#define JP_UART_H

#include "BCM2835.h"

#define BAUD_DIV_9600 (3254)

extern void
UART_PutC(char c);

extern void
UART_Puts(char *str);

extern void
UART_PutB(char *str, u32 size);

extern void
UART_Printf(const char *fmt, ...);

extern char
UART_GetC(void);

extern u32
UART_GetS(char *str);

#endif