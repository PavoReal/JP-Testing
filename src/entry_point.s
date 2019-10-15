
//
// Entry point
//
.globl _start
_start:
.func _start
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
