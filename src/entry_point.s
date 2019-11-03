
//
// Entry point
//
.globl _start
_start:
.func _start
    mov sp,#0x8000
    bl start

hang: b hang
.endfunc

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

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
