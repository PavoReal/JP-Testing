#if !defined(JP_UART_H)
#define JP_UART_H

#include "BCM2835.h"

#define BAUD_DIV_9600 (3254)

#define UART_PutNewline() UART_PutC('\r'); UART_PutC('\n')

extern void
UART_PutC(char c);

extern void
UART_PutHex(u32 data);

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

extern void
UART_Flush(void);

#endif