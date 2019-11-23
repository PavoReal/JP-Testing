#include <stdio.h>
#include <stdlib.h>

#include "Platform.h"

extern void
PUT32(u32, u32);

extern u32
GET32(u32);

#define MMUTABLEBASE 0x00004000

extern void start_mmu ( unsigned int, unsigned int );
extern void stop_mmu ( void );
extern void invalidate_tlbs ( void );
extern void invalidate_caches ( void );

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

    UART_Flush();
}

unsigned int mmu_section ( unsigned int vadd, unsigned int padd, unsigned int flags )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(padd&0xFFF00000)|0xC00|flags|2;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc);
    return(0);
}

unsigned int mmu_small ( unsigned int vadd, unsigned int padd, unsigned int flags, unsigned int mmubase )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(mmubase&0xFFFFFC00)/*|(domain<<5)*/|1;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc); //first level descriptor
    ra=(vadd>>12)&0xFF;
    rb=(mmubase&0xFFFFFC00)|(ra<<2);
    rc=(padd&0xFFFFF000)|(0xFF0)|flags|2;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc); //second level descriptor
    return(0);
}

int 
start(void)
{
    SetupUART();
    StartUART();

    u32 ra;
    for(ra=0;;ra+=0x00100000)
    {
        mmu_section(ra,ra,0x0000);
        if(ra==0xFFF00000) break;
    }

    mmu_section(0x20000000,0x20000000,0x0000); //NOT CACHED!
    mmu_section(0x20200000,0x20200000,0x0000); //NOT CACHED!

    start_mmu(MMUTABLEBASE,0x00000001|0x1000|0x0004); //[23]=0 subpages enabled = legacy ARMv4,v5 and v6

    u8 *m = (u8*) malloc(1024);
   
    UART_Printf("Hello JP, Version %s\r\n%0x\n%u", JP_VERSION, m, *m);

    while (1)
    {
        char buffer[1024];
        UART_GetS(buffer);
        UART_Printf("> %s\r\n", buffer);
    }

    return EXIT_SUCCESS;
}
