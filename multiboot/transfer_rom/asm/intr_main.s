    .include "asm/constants.inc"
    .include "asm/macros.inc"

    .syntax unified

	arm_func_start IntrMain
IntrMain: @ 0x02000104
	mov r3, REG_BASE
	add r3, r3, REG_IE_OFFSET
	ldr r2, [r3]
	ldrh r1, [r3, (REG_IME_OFFSET - REG_IE_OFFSET)] @ Interrupt Master Enable
	mrs r0, spsr
	push {r0-r3, lr}
	mov r0, #1
	strh r0, [r3, (REG_IME_OFFSET - REG_IE_OFFSET)] @ Interrupt Master Enable
	and r1, r2, r2, lsr #16
	mov ip, #0
	ands r0, r1, #0x80
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x40
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #1
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #2
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #4
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #8
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x10
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x20
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x100
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x200
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x400
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x800
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x1000
	bne _020001D4
	add ip, ip, #4
	ands r0, r1, #0x2000
	strbne r0, [r3, #-0x17c]
_020001D0:
	bne _020001D0
_020001D4:
	strh r0, [r3, #2]
	mov r1, #0x20c0
	bic r2, r2, r0
	and r1, r1, r2
	strh r1, [r3]
	mrs r3, apsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x1f
	msr cpsr_fc, r3
	ldr r1, _02000238 @ =0x02007E5C
	add r1, r1, ip
	ldr r0, [r1]
	stmdb sp!, {lr}
	add lr, pc, #0x0 @ =0x02000210
	bx r0
	ldm sp!, {lr}
	mrs r3, apsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x92
	msr cpsr_fc, r3
	pop {r0, r1, r2, r3, lr}
	strh r2, [r3]
	strh r1, [r3, #8]
	msr spsr_fc, r0
	bx lr
	.align 2, 0
_02000238: .4byte sIntrTable
