
//
// Entry point
//
.globl _start
_start:
.func _start
	;@ enable fpu
	mrc p15, 0, r0, c1, c0, 2
    orr r0,r0,#0x300000 ;@ single precision
    orr r0,r0,#0xC00000 ;@ double precision
    mcr p15, 0, r0, c1, c0, 2
    mov r0,#0x40000000
    fmxr fpexc,r0

    mov sp,#0x8000
    bl main

hang: b hang
.endfunc

//
// Simply returns
//
.globl nop
nop:
.func nop
    bx lr
.endfunc

//
// See void dmb(void) in Arm.h
//
.globl dmb
dmb:
.func dmb
	mov	r12, #0
	mcr	p15, 0, r12, c7, c10, 5
	bx lr
.endfunc
